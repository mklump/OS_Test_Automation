@rem --*-Perl-*--
@if "%overbose%" == "" if "%_echo%"=="" echo off
if not exist "%~dp0oenvtest.bat" (perl -x "%~dpnx0" %* & goto :eof)
setlocal
call %~dp0oenvtest.bat
"%~dp0%PROCESSOR_ARCHITECTURE%\perl%OPERLOPT%" -wx "%~dpnx0" %*
goto :eof

#!/usr/bin/perl -w

require 5.004;
die "Unsupported OS ($^O), sorry.\n" 
    unless ($^O =~ /^MSWin(32|64)$/ or $^O eq 'darwin'); 

BEGIN {

    # set library path for OTOOLS environment
    if ($^O =~ /^MSWin(32|64)$/ and defined $ENV{"OTOOLS"}) {
        require "$ENV{'OTOOLS'}\\lib\\perl\\otools.pm"; import otools;
    }

    # Convert "use strict 'subs'" to the eval below so we don't
    # barf if the user's @INC is set up wrong.  You'd be surprised
    # how often this happens.
    eval { require strict; import strict 'subs' };
}

binmode(DATA, ':crlf');

sub Usage {
    my $usage;
    for $usage (split(/\n/, <<'EOM')) {
NAME

$name - create a buddy build package

SYNOPSIS

    $name -?|-h

    $name [-c changelist] [-C "comment"] [-CD] [-d] [-f] 
          -o outputfile [-q] [-r] [-v-] [-x filename] [-FO] [-FN]
          [filelist]

DESCRIPTION

    Combines up all files in a changelist into a self-contained
    package which can be used later to replicate the changelist
    on another (or the same) machine.

    If neither a changelist nor a filelist is specified on the
    command line, all files in the default changelist are used.


OPTIONS

    -? or -h

        Displays this help file.

    -c changelist

        Collect files from the specified changelist.  As a special
        case, "-c all" requests all changelists, overriding the
        default of "-c default".  Note that when a package is created
        from files from multiple changelists, they will still unpack
        into a single changelist.

    -C  "comment"

        Attach a comment to the package.  This comment is displayed at
        the top of the -l output.

    -CD

        Attach a change description to the package.  The change description
        is displayed with the -l output.  This in only valid with a numeric
        changelist specified by -c.

    -d

        Turns on debugging spew to stdout.  To avoid mixing debugging
        output from normal output, send the normal output to a file
        via the -o switch.

    -f

        Overwrite the output file if it already exists.

    -o outputfile
    -o -

        Generate the output to the specified file (or stdout if "-"
        is given as the filename).
O|
O|      If no extension is provided, the ".bpk" extension will be
O|      assumed.

    -q

        Run quietly.  Diagnostics are suppressed; only warnings
        and errors are displayed.

    -r

        Register $name as handler for the .bpk extension.
        NOTE: This is done automatically for the Office flavor.

    -v-

        Disable autoverify.  By default, $name verifies the package
        after building it if the output is to a file.  (Output to
        stdout cannot be verified.  Sorry.)

    -x filename

        Read the filelist from the specified file (or stdin if "-"
        is given as the filename).

    -FO
    -FN

        Set the $name flavor.  O = Office project, N = NT project.

        See additional remarks below for a discussion of flavors.

    filelist

        Optional list of files to be included in the package.
        If no filelist is specified, then all files in the default
        changelist (or the changelist named by the -c option)
        are included in the package.

        sd wildcards are permitted here (such as "..." to package
        all files in the current directory and below).

OUTPUT

    Output is a batch file which can be run on the same or another
    enlistment (into the same branch) to replicate the changelist
    on the target machine.

    See below (under "outputfile") for usage instructions for the
    output file.

FLAVORS

    If the OTOOLS environment variable is defined, possibly by a
    successful, implicit call to oenvtest.bat, $name assumes
    the Office flavor; otherwise, it assumes the NT flavor.  You
    can override this decision by using the -F command line option.

    The Office flavor differs from the NT flavor in the following
    aspects:

        Office flavor registers $name as the handler for
        the .bpk file extension.  NT flavor does not.

        Office flavor appends the ".bpk" extension to the output
        file name if no extension is provided.  NT flavor does not
        assume an extension.

EXAMPLE

    Suppose you want to send your default changelist to Bob for
    a buddy build before you check the files in.

N|      $name -o buddybuild.cmd
O|      $name -o buddybuild

N|  You then copy buddybuild.cmd to a convenient location
O|  You then copy buddybuild.bpk to a convenient location
    or send it via email to Bob.

    Bob types

N|      buddybuild.cmd -u
O|      buddybuild.bpk -u

    The batch file first determines whether it is safe to unpack
    itself.  If so, it regurgitates its contents into the
    default changelist.

    Bob can then do whatever he likes with the changelist.  He can
    perform a code review with "sd diff".  He can launch a buddy
    build.  He can even submit it on your behalf.  Or he can revert
    the entire changelist, thereby undoing the effect of running
N|  the buddybuild.cmd batch file.
O|  the buddybuild.bpk batch file.

EXAMPLE

    Suppose you're working on a change, but you get tagged to fix a
    BVT break that requires changing a file you are already working on.
    You don't want to create a branch just for this one-off fix.

    Create a package that consists of all the files you were
    working on.

N|      $name -o %INIT%\hold.cmd
O|      $name -o %INIT%\hold

N|  (Notice that the file was output to your developer directory
N|  so it won't get scorched.)
O|  (This assumes that you have set the INIT environment variable
O|  to some safe directory.)

    Revert the changelist that you just packaged up.

        sd revert -c default ...

    Check in your BVT fix.  (sd edit, build, sd submit)

    Restore the package you saved away.

N|      %INIT%\hold.cmd -s -u
O|      %INIT%\hold.bpk -s -u

    Continue your work.

EXAMPLE

    Suppose you're working on a change and you've reached a stage
    where you've made a lot of progress but you're about to embark
    on some serious rewriting and you don't want to lose what you've
    done so far in case your rewrite turns out to be a bad idea.

    Create a package that consists of all the files you were
    working on.

N|      $name -o %INIT%\before_rewrite.cmd
O|      $name -o %INIT%\before_rewrite

    Do your rewrite.  If you decide that your rewrite was a bad idea,
    you can back up to the package that you saved.

        sd revert -c default ...
N|      %INIT%\before_rewrite.cmd -u
O|      %INIT%\before_rewrite.bpk -u

    Paranoid people like me do this periodically and save the packages
    on another machine.

EXAMPLE

    Suppose you're working on a change and you have to take your
    work and move it to another branch.  (Maybe your team moved branches,
    or your bug got marked as Critical and needs to be spotfixed in
    another branch.)

    From the branch you are currently working in, create a package
    that consists of all the files you want to transfer.

N|      $name -o %INIT%\xfer.cmd
O|      $name -o %INIT%\xfer

    Go to an enlistment in the branch you want to transfer to and
    unpack in merge mode.

N|      %INIT%\xfer.cmd -m //depot/oldbranch/ //depot/newbranch/
O|      %INIT%\xfer -m //depot/oldbranch/ //depot/newbranch/

LIMITATIONS

    The files in the package must be text or binary files with history.
    Unrecoverable files cannot be packaged.

    Files to be packaged must all come from a single depot.  Multi-depot
    packages are not supported.  Create multiple packages instead.

    The -c flag is not consulted to determine whether there are any
    unresolved opened files.  That's because the "sd resolve" command
    does not accept a -c option.

WARNINGS

O|  warning: cannot register .bpk file extension; continuing
O|
O|      $name couldn't write to the registry to enable
O|      double-clicking of files with the .bpk extension.  Your
O|      perl installation may be incomplete.  $name will continue
O|      creating your package anyway.
O|
    //depotpath: unrecoverable; skipping

        Unrecoverable files cannot be packaged
        by $name.  They will be omitted from the resulting package.

    //depotpath: cannot package cmd; skipping

        The type of change is not one of the types supported by
        $name (add, delete, edit).  The file will be omitted from
        the resulting package.

    //depotpath: will treat integrate as "edit"
    //depotpath: will treat branch as "add"
    //depotpath: will treat X-undo as "X"

        The changelist contains "integrate", "branch" or "undo" records.
        $name does not know how to regenerate these changes, so it
        will instead treat them as described in the message.

ERRORS

    error: Can't tell who you are, sorry

        $name was unable to connect to the Source Depot server to
        determine your identity.  Make sure the server is up and you
        are running $name from the correct directory.

    error: You need to sd resolve before you can run $name

        There are changes that have not yet been resolved.
        $name cannot re-create an unresolved edit.

    error: outputfile exists; use -f -o to force overwrite

        By default, $name refuses to overwrite an existing file.
        Use the -f switch to force an overwrite.

    internal error: Cannot run sd diff

        The Source Depot "sd diff" command failed for some reason.

    internal error: filename in sd diff output but not in changelist

        The Source Depot "sd diff" command generated a diff entry for
        a file that wasn't listed in the output of "sd opened".

        Make sure you aren't running a Source Depot command in another
        window at the same time you are running $name.

    internal error: filename#rev in sd diff output; expected filename#rev2

        The Source Depot "sd diff" command generated a diff entry for
        a version of the file different from the one listed in the output
        of "sd opened".

        Make sure you aren't running a Source Depot command in another
        window at the same time you are running $name.

    internal error: filename in sd diff output twice?

        The Source Depot "sd diff" command generated two diff entries
        for the same file.  $name can't tell which one to trust.

    internal error: parsing sd diff output (expecting header)
    internal error: parsing sd diff output (expecting header or a/d)
    error: Could not parse output of sd diff

        $name had trouble parsing the output of the "sd diff" command,
        perhaps because one of the files participating in the diff
        does not end in a newline and you have an old version of Source
        Depot (fixed in 2.7, dunno about earlier versions).

        (Old versions of Source Depot emitted corrupted diffs if a file
        in the diff did not end in a newline.)

        If $name finds a file without a newline, it tries to repair
        the diff produced by "sd diff", and usually it guesses right,
        but sometimes it guesses wrong.

        In environments running pre-2.0 versions of Source Depot, a
        potential reason is that you've asked $name to do Source Depot
        operations requiring the server to handle more than MaxResults
        records.  Specify lists of individual files to work around this
        limit.

    error: cannot open filename for reading (reason)
    error: cannot open filename for writing (reason)

        The specified error occurred attempting to open the indicated
        file.

    error: writing (reason)

        The specified error occurred attempting to write to
        the output file (usually out of disk space).

DESIGN CONSIDERATIONS

    The design goals of $name were not entirely unreasonable at the time
    it was written, but today they seem quote outdated and irrelevant.

    -   Packages were self-extracting so people wouldn't say,
        "What?  I have to install this program just to do your code
        review?  Dream on!"

    -   sdapi and the CLR did not exist at the time.

    -   Package size was important because people's mailboxes were always
        near quota.  (Arguably, this is still true.)

    -   Plain text format was a logical consequence of the
        self-extracting nature, since it forced the package to be
        in the form of a batch file.

    The requirement for the package to be self-extracting also solved
    the versioning problem, since the package contains its own
    extractor.  You will never get stuck with a package that cannot
    be extracted due to a file format change.

    I am occasionally tempted to rewrite bbpack based on more modern
    design goals, but then I realize that I would just be wasting my
    time.  It would end up being a clone of sdpack or jjpack.
    (See http://toolbox for these "second generation" client state
    persistence/transport tools.)

REMARKS

    4NT users need to type

        perl -Sx $name.cmd

    instead of just $name.  You can create a 4NT alias

        alias $name=perl -Sx $name.cmd

    if you use this script a lot.

ENVIRONMENT

    Since $name runs sd internally, all the SD environment variables
    also apply.

BUGS

    The heuristic for auto-repairing broken "sd diff" output
    can fail if the file contains the string "==== //".

VERSION

O|  This is version $packver (Office flavor) of $name.
N|  This is version $packver (NT flavor) of $name.

AUTHOR

    raymondc.  Office flavor by smueller.
    Mac support by nathanh and jecollin.

----------------------- HELP ON HOW TO UNPACK ---------------------------

EOM
        $usage =~ s/\$name/$main::name/g;
        $usage =~ s/\$packver/$main::packver/g;
        $usage =~ s/^$main::F\|/  /;
        next if $usage =~ /^.\|/;
        print $usage, "\n";
    }

    # Now get the usage string from the output.
    0 while <DATA> ne "    my \$usage = <<'EOM';\n";
    while (($usage = <DATA>) ne "EOM\n") {
        $usage =~ s/\$name/outputfile/g;
        $usage =~ s/\$packver/$main::packver/g;
        $usage =~ s/\$pack/$main::name/g;

        # prevent false positives when searching for the magic cookie
        $usage =~ s/_!_/__/g;

        print $usage;
    }
}

sub dprint {
    print "# ", @_, "\n" if $main::d;
}

sub vprint {
    print @_ unless $main::q;
}

sub Emit {
    print O @_ or die "error: writing ($!)\n";
}

sub SpewBinaryFile {
    local($/);
    my $file = shift;
    open(B, $file) or die "error: cannot open $file for reading ($!)\n";
    binmode(B);
    Emit pack("u", scalar <B>), "\n";
    close(B);
}

sub SpewLinkFile {
    Emit pack("u", readlink(shift)), "\n";
}

sub FileMissingNewline {
    my $file = shift;
    return 0 if -z $file; # zero-length file doesn't need newline
    open(B, $file) or die "error: cannot open $file for reading ($!)\n";
    binmode(B);
    seek(B, -1, 2);
    my $result = scalar(<B>) ne "\n";
    close(B);
    $result;
}

@main::warnings = ();
sub Warning {
    warn $_[0];
    push(@main::warnings, $_[0]);
}

sub RepeatWarnings {
    if (@main::warnings)
    {
        warn "---- WARNING SUMMARY ----\n";
        for my $warning (@main::warnings) {
            warn $warning;
        }
    }
}

sub QuoteSpaces {
    wantarray ? map { / / ? "\"$_\"" : $_ } @_
              : $_[0] =~ / / ? "\"$_[0]\"" : $_[0];
}

sub CreateTempFile {
    my $TEMP = $ENV{"TEMP"} || $ENV{"TMP"} || '/tmp';
    die "error: no TEMP directory" unless -d $TEMP;
    $TEMP =~ s/\\$//;     # avoid the \\ problem

    $tempfile = "$TEMP/bbpack.$$";
    open(T, ">$tempfile") || die "error: Cannot create $tempfile\n";
    my $success = print T @_;
    $success = close(T) && $success;
    unlink $tempfile, die "error: writing $tempfile ($!)\n" unless $success;
    $tempfile;
}

#
#   A "ChangeEntry" is a single line in a change list.
#   It is a hash of the form
#
#   depotpath => //depot/blahblah
#   localpath => C:\nt\blahblah
#   rev => revision
#   cmd => "edit", "add" or "delete"
#   type => "text" or whatever
#

package ChangeEntry;

sub dprint { main::dprint @_ } # For debugging

# Constructs from a line in the "sd -s opened" output
sub new {
    my ($class, $line) = @_;
    $line =~ m|^info: (//.*?)#(\d+) - (\S+) .* \((.*?)\)| || return undef;
    my $self = {
        depotpath => $1,
        rev => $2,
        cmd => $3,
        type => $4,
    };
    bless $self, $class;
}

sub SetLocalPath {
    my ($self, $localpath) = @_;
    $self->{localpath} = $localpath;
    ($self->{atime}, $self->{mtime}) = (stat $localpath)[8,9];
}

sub Format {
    my $self = shift;
    $self->{cmd} eq 'delete' ? $self->ShortFormat :
        "$self->{depotpath}#$self->{rev} $self->{cmd} $self->{type} $self->{atime} $self->{mtime}";
}

sub ShortFormat {
    my $self = shift;
    "$self->{depotpath}#$self->{rev} $self->{cmd} $self->{type}";
}

sub dump {
    my ($self, $caller) = @_;
    dprint "$caller: ", $self->Format, " = $self->{localpath}\n";
}

#
#   A ChangeList is a list of files to be packaged.
#   It is a hash of the form
#
#   list => a hash, keyed by depot path, of ChangeEntry's
#   skipped => number of files skipped
#   add => number of files added
#   del => number of files deleted
#   edit => number of files edited
#
#   We break from generality and do ChangeList pruning in situ.
#
package ChangeList;

sub dprint { main::dprint @_ } # For debugging
sub Warning { main::Warning @_ }

sub new {
    my ($class, $change) = @_;
    my $list = { };
    my $self  = {
        list => $list,
        skipped => 0,
        add => 0,
        delete => 0,
        edit => 0,
    };
    bless $self, $class;

    my @help = ();  # Files we need help locating

    dprint "sd opened $change";
    foreach $line (`sd -s opened $change 2>&1`) {
        next if $line =~ /^warning: / || $line =~ /^exit: / || $line =~ /^This depot has not been successfully backed up in/
            || $line =~ /^Last successful backup was/;
        my $entry = new ChangeEntry($line);
        $entry or die "error: $line";
        #dprint $entry->{depotpath};

        if ($entry->{type} !~ /(text|binary|unicode|symlink)/) {
            Warning "$entry->{depotpath}: is unknown type; skipping\n";
            $self->{skipped}++;
            next;
        } elsif ($entry->{type} =~ /S/) {
            Warning "$entry->{depotpath}: unrecoverable; skipping\n";
            $self->{skipped}++;
            next;
        }

        # Some rewrite rules to convert things we don't support into
        # things we do.
        if ($entry->{cmd} =~ /^(.*)-undo$/) {
            Warning "$entry->{depotpath}: will treat $entry->{cmd} as \"$1\"\n";
            $entry->{cmd} = $1;
        }

        if ($entry->{cmd} eq "integrate") {
            Warning "$entry->{depotpath}: will treat $entry->{cmd} as \"edit\"\n";
            $entry->{cmd} = "edit";
        } elsif ($entry->{cmd} eq "branch") {
            Warning "$entry->{depotpath}: will treat $entry->{cmd} as \"add\"\n";
            $entry->{cmd} = "add";
        }

        # Now study the result after we have finished munging the {cmd}
        if ($entry->{cmd} =~ /^(add|delete)$/) {
            push(@help, $entry->{depotpath});
        } elsif ($entry->{cmd} ne "edit") {
            Warning "$entry->{depotpath}: cannot package $entry->{cmd}; skipping\n";
            $self->{skipped}++;
            next;
        }
        $self->{$entry->{cmd}}++;
        $list->{lc $entry->{depotpath}} = $entry;
        dprint "$entry->{depotpath}#$entry->{rev}";
    }

    # Now add local paths to all the add/delete's in the ChangeList.
    if (@help) {
        my $tempfile = main::CreateTempFile(join("\n", @help), "\n");
        local($/) = ""; # "sd where -T" emits paragraphs
        dprint "sd -x \"$tempfile\" where";
        foreach $line (`sd -x "$tempfile" where -T _ 2>&1`) {
            my($depotFile) = $line =~ m|^\.\.\. depotFile (.+)|m;
            next unless $depotFile;
            my $entry = $self->GetEntry($depotFile);
            next unless $entry;
            my($path) = $line =~ m|^\.\.\. path (.+)|m;
            next unless $path;
            if ($line =~ m|^\n\n\n unmap|m) {
                delete $entry->{localpath};
            } else {
                $entry->SetLocalPath($path);
            }
            dprint "$depotFile -> $path";
        }
        unlink $tempfile;
    }

    # All done.
    $self;
}

sub GetEntry {
    my ($self, $depotpath) = @_;
    $self->{list}->{lc $depotpath};
}

sub GetAllEntries {
    my $self = shift;
    values %{$self->{list}};
}

sub dump {
    my ($self, $caller) = @_;
    for my $entry ($self->GetAllEntries()) {
        $entry->dump($caller);
    }
    dprint "$caller: .";
}

package Register;

sub Warning { main::Warning @_ }

#
# RegBpk - Register .bpk file extension and create file association.
# Note that RegBpk is called early; can't assume much.
#
sub RegBpk {

        eval { require Win32::Registry; import Win32::Registry };
        if ($@) {
            Warning "warning: cannot register .bpk file extension; continuing\n";
            return;
        }

        # assoc .bpk=BBPackage
        my ($hkey, $hkeyNew, $diffcmd, $listcmd);
        if ($main::F eq 'O') {
            my $binarch = "$ENV{OTOOLS}\\bin\\$ENV{PROCESSOR_ARCHITECTURE}";
            my $libperl = "$ENV{OTOOLS}\\lib\\perl";
            my $perl = qq/"$binarch\\perl.exe" -I "$libperl" -x/;
            my $setup = "set OTOOLS=$ENV{OTOOLS}& set PATH=$binarch;%PATH%";

            {
                no warnings qw(syntax once);
                $hkey = $HKEY_LOCAL_MACHINE;
            }
            
            $diffcmd = qq!cmd.exe /c ($setup& $perl.exe "%1" -w %*)!;
            $listcmd = qq!cmd.exe /c ($setup& $perl.exe "%1" -l %*& pause)!;
        } else {
            # rely on normal path for non-Office registration
            {
                no warnings qw(syntax once);
                $hkey = $HKEY_CURRENT_USER;
            }
            my $perldir = $^X;
            $perldir =~ s/\\[^\\]*$//;
            my $setup = "set PERL5LIB=$ENV{PERL5LIB}& set PATH=$ENV{PATH};$perldir";
            $diffcmd = qq!cmd.exe /c ($setup& $perl -x "%1" -w %*)!;
            $listcmd = qq!cmd.exe /c ($setup& $perl -x "%1" -l %*& pause)!;
        }

        if ($hkey->Create('SOFTWARE\\Classes\\.bpk', $hkeyNew)) {
                $hkeyNew->SetValueEx('', 0, &REG_SZ, 'BBPackage');
                $hkeyNew->Close();
        }

        # ftype BBPackage=cmd.exe /c (set OTOOLS/PATH & perl.exe -I LIB -x "%1" -w %*)
        # (i.e., shell context menu Open command)
        if ($hkey->Create(
                'SOFTWARE\\Classes\\BBPackage\\Shell\\Open\\Command', $hkeyNew)) {
                $hkeyNew->SetValueEx('', 0, &REG_EXPAND_SZ, $diffcmd);
                $hkeyNew->Close();
        }

        # default is usually Open, but let's be explicit
        if ($hkey->Create(
                'SOFTWARE\\Classes\\BBPackage\\Shell', $hkeyNew)) {
                $hkeyNew->SetValueEx('', 0, &REG_SZ, 'Open');
                $hkeyNew->Close();
        }

        # shell context menu Log command
        if ($hkey->Create(
                'SOFTWARE\\Classes\\BBPackage\\Shell\\Log\\Command', $hkeyNew)) {
                $hkeyNew->SetValueEx('', 0, &REG_EXPAND_SZ, $listcmd);
                $hkeyNew->Close();
        }
}

package main;

#
#   Okay, now initialize our globals.
#

$main::name = $0;
$main::name =~ s/.*[\/\\:]//;
$main::name =~ s/\.(bat|cmd)$//i;
$main::userid = $ENV{"USER"} || $ENV{"USERNAME"} || getlogin || "userid";
($main::packver) = '$Id: bbpack.cmd#112 2007/08/31 10:23:06 $' =~ /#(\d+)/;

$main::c = undef;
$main::C = undef;
$main::CD = 0;
$main::d = 0;
$main::f = 0;
$main::o = undef;
$main::q = 0;
$main::r = 0;
$main::v = 1;
@main::x = ();
$main::F = ($^O eq 'darwin' or defined $ENV{"OTOOLS"}) ? "O" : "N"; # Set default flavor
$main::oCleanup = undef;
$main::cmd = 0;

$main::nul = ($^O eq 'darwin') ? '2>/dev/null' : '2>nul';

# Allow "bbpack /?" to be an alias for "bbpack -?"
while ($#ARGV >= 0 && ($ARGV[0] =~ /^-/ || $ARGV[0] eq '/?')) {
    my $switch = shift;
         if ($switch eq '-c') {
        $main::c = shift;
    } elsif ($switch eq '-C') {
        $main::C = shift;
    } elsif ($switch eq '-CD') {
        $main::CD++;
    } elsif ($switch eq '-d') {
        $main::userid = "userid";
        $main::d++;
    } elsif ($switch eq '-f') {
        $main::f++;
    } elsif ($switch eq '-o') {
        $main::o = shift;
    } elsif ($switch eq '-q') {
        $main::q++;
    } elsif ($switch eq '-r') {
        $main::r++ if ($^O ne 'darwin');
    } elsif ($switch eq '-v-') {
        $main::v = 0;
    } elsif ($switch eq '-x') {
        push(@main::x, shift);
    } elsif ($switch eq '-FN') {
        $main::F = 'N';
    } elsif ($switch eq '-FO') {
        $main::F = 'O';
    } elsif ($switch eq '-?' || $switch eq '/?' || $switch eq '-h') {
        if ($main::F eq 'O' and $^O ne 'darwin') {
            Register::RegBpk();             # Office flavor creates association
        }
        Usage(); exit 1;
    } else {
        die "Invalid command line switch; type $name -? for help\n";
    }
}

if ($main::r || ($main::F eq 'O' and $^O ne 'darwin')) {
    Register::RegBpk();                # Office flavor creates association
}

die "Mandatory -o parameter missing; type $name -? for help\n"
    unless defined $main::o;        # Output file should be specified

if ($main::CD && (!$main::c || ($main::c && !($main::c =~ /^\d+$/)))) {
    die "Cannot use -CD without numeric changelists in -c; type $name -? for help\n";
}

#
#   Get some preliminary information.
#
my %ClientProperties;
@RequiredProperties = ("Client name", "User name", "Server address");

{
    # Intentionally let errors through to stderr
    foreach my $line (`sd info`) {
        $ClientProperties{$1} = $2 if $line =~ /^(.*?): (.*)$/;
    }

    foreach my $prop (@RequiredProperties) {
       die "error: Can't tell who you are, sorry\n"
           unless $ClientProperties{$prop};
    }
}

#
#   Global filehandles:
#
#       O = output file
#       SD = sd command

if ($main::o eq '-') {
    open(O, ">&STDOUT");
} else {
    # Office flavor appends default extension
    $main::o .= '.bpk' if $main::F eq "O" && $main::o !~ /\./;

    die "error: $main::o exists; use -f -o to force overwrite\n"
        if !$main::f && -e $main::o;
    open(O, ">$main::o") or die "error: $main::o: $!\n";
    chmod 0755, $main::o;
    $main::oCleanup = $main::o;
}
$main::cmd = 1 if ($main::o =~ /\.(bat|cmd)$/i);
binmode(O, ":crlf") if $main::cmd; # enforce windows line endings for CMD files.

dprint ">$main::o";

#
#   Dump .cmd goo for NT style packs
#
if ($main::cmd) {
    my $cmdgoo = <<'CMD_GOO';
@rem --*-Perl-*--
@if "%overbose%" == "" if "%_echo%"=="" echo off
setlocal
for %%i in (oenvtest.bat) do call %%~$PATH:i
perl -x "%~dpnx0" %*
goto :eof

CMD_GOO
    Emit ($cmdgoo);
}

#
#   Dump the header.
#
{
    my $line;
    while ($line = <DATA>) {
        $line =~ s/\$packver/$main::packver/;
        Emit $line;
    }
}

#
#   Dump out the perl bug-detector.
#
Emit "PerlSniffTest: ", "."x256, "\n";

#
#   Dump out some meta-data.
#
{
    Emit "Packager: $main::name\n";
    foreach my $prop (@RequiredProperties) {
       Emit "$prop: $ClientProperties{$prop}\n";
    }

    my @today = localtime(time);
    my $datetime = sprintf "Date: %04d/%02d/%02d %02d:%02d:%02d\n",
             1900+$today[5], 1+$today[4], $today[3],
             $today[2], $today[1], $today[0];
    Emit $datetime;
}

#
#   Dump out the comment
#
if (defined $main::C) {
    Emit "Comment: $main::C\n"
}

#
#   Gather up and dump out the changelist comments
#

if ($main::CD) {
    my $count = 0;
    foreach my $line (`sd -s describe -s $main::c 2>&1`) {
    $line = chomp($line);
    if ( ( $line =~ /^text: (Change .*)$/ ) ||
         ( $line =~ /^text: (\t.*)$/ ) ) {
        Emit "Change Description: $1\n";
        $count++;
        Emit "Change Description: \n" if ( 1 == $count ); # spacer
    }
    }
}

Emit "\n";

#
#   Gather up the files that belong to change $main::c and perhaps
#   also the files remaining on the command line.
#

# If no changelist or file list provided, then use -c default.
$main::c = "default" if $#ARGV < 0 && !$main::c && !@main::x;

# "-c all" means "all changelists"
$main::c = "" if $main::c && $main::c eq "all";

my $ChangeSpec = $main::c ? "-c $main::c" : "";
@ARGV = QuoteSpaces(@ARGV);
$ChangeSpec .= " @ARGV" if $#ARGV >= 0;

#
#   Now add in the stuff from all the -x files.
#
foreach (@main::x) {
    open(I, $_) or die "error: cannot open $_ for reading ($!)\n";
    while (<I>) {
        chomp;
        $_ = "\"$_\"" if / / && !/"/;
        $ChangeSpec .= " $_";
    }
    close(I);
}

{
    my $line = `sd resolve -n @ARGV 2>&1`;
    die "error: You need to sd resolve before you can run $main::name.\n".
        "\n".
        "Unresolved files reported by \"sd resolve -n @ARGV\":\n".
        "\n".
        "$line\n"
        unless $line =~ /[Nn]o file\(s\) to resolve\.$/;
}

vprint "Collecting files from \"sd opened $ChangeSpec\"\n";
my $ChangeList = new ChangeList($ChangeSpec);


vprint "Collecting files done (",
       join(", ", map { "$ChangeList->{$_} $_" } qw(edit add delete skipped)),
       ")\n";

#
#   Emit the file list, terminated by a blank line.
#
#   Sort the file list for prettiness.  Makes it easier to read.
#
foreach my $entry (sort { lc $a->{depotpath} cmp lc $b->{depotpath} }
                  $ChangeList->GetAllEntries()) {
    Emit $entry->ShortFormat, "\n";
}

Emit "\n";

#
#   Run a giant "sd diff" to collect the bulk of the information
#   The end of each diff is marked with a "q".

if ($ChangeList->{edit}) {


    my $copy = 0;           # number of lines to copy blindly to output
    my $files = 0;          # number of files processed
    my $entry;              # file being processed
    my $possibleBad = "";   # file that might be missing a newline
    my $line;
    my $tempfile;
    my $fUnicodeFile = 0;

    #
    #   If the user has overridden SDDIFF in their sd config, we'll have
    #   to temporarily reconfigure them.  (Same goes for SDUDIFF.)
    #
    #   First, try it the easy way: Remove SDDIFF from the environment.
    #
    delete $ENV{"SDDIFF"};
    delete $ENV{"SDUDIFF"};

    #   Secret environment variable that also messes up sd...
    #   Delete it while we still can.
    delete $ENV{"DIFF"};

    #
    #   Next, see if the user has overridden SDDIFF by "sd set SDDIFF=..."
    #
    if (`sd set SDDIFF SDUDIFF` =~ /^(SDDIFF|SDUDIFF)=/im) {
        #
        # Darn, we have to unset it by creating a temporary INI file
        # that explicitly clears SDDIFF and SDUDIFF.
        #
        $tempfile = CreateTempFile("SDDIFF=\nSDUDIFF=\n");
        $ENV{"SDPORT"} = $ClientProperties{"Server address"};
        $ENV{"SDCLIENT"} = $ClientProperties{"Client name"};
        $ENV{"SDCONFIG"} = $tempfile;

        dprint "Force SDCONFIG=$ENV{'SDCONFIG'}";
        dprint "Force SDPORT=$ENV{'SDPORT'}";
        dprint "Force SDCLIENT=$ENV{'SDCLIENT'}";
    }

    #   Okay, we're ready to do the diff thing.


    dprint "sd diff -dn $ChangeSpec";
    open(SD, "sd diff -dn $ChangeSpec $main::nul|") or die "internal error: Cannot run sd diff\n";

    # Keep track of whether we are expecting a file without a newline
    my $missingNewline = 0;

    while ($line = <SD>) {
        # Unlink the temp file the moment we get output, in case we die
        unlink($tempfile), $tempfile = undef if $tempfile;

        # Reset some flags if we hit a new file in the output
        $fUnicodeFile = $missingNewline = 0
            if $line =~ m,^==== //.*?#\d+ - .+ ====,;

        next if $fUnicodeFile;
        next if substr($line, -1) eq "";

        die "error: Could not parse output of sd diff\n".
            "file $entry->{localpath} does not end in newline\n"
           unless substr($line, -1);

        if ($copy > 0) {
            $copy--;
            if ($copy == 0 && $missingNewline) {
                #   Heuristic: If we see a new file start tag, assume
                #   it really is a new file start. Split the line and
                #   treat it as two lines.
                if ($line =~ m,^(.*)(==== //.*?#\d+ - .+ ====.*)$,s) {
                    $possibleBad .= "-- it might be $entry->{localpath}\n";
                    Emit $1, "\n";
                    $line = $2;
                    redo;
                }
            }
            if (substr($line, -1) ne "\n") {
                $line .= "\n";
                $missingNewline = 0;
            }
            Emit $line;             # Just copy the line to the output
        } elsif ($line =~ /^==== (.*?)#(\d+) - (.+) ====(.*)$/) { # New file starting?
            #
            #   $1 = depotpath
            #   $2 = rev
            #   $3 = localpath
            #   $4 = isbinary

            Emit "q\n" if $entry;       # Finish the previous diff

            $entry = $ChangeList->GetEntry($1) or die "internal error: $1 in sd diff output but not in changelist\n";
            $entry->{rev} == $2 or die "internal error: $1#$2 in sd diff output; expected #$entry->{rev}\n";
            $entry->{localpath} and die "internal error: $1 in sd diff output twice?\n";
            $entry->SetLocalPath($3);
            vprint "edit $3\n";
            $files++;
            $missingNewline = 0;

            # the // below will corrupt $n so save these before it's too late
            my ($localpath, $isbinary) = ($3, $4);

            if ($entry->{type} =~ /binary|unicode/ ||
                !FileMissingNewline($entry->{localpath})) {
            } else {
                $entry->{type} .= "_nonewline";
                $missingNewline = 1;
            }
            Emit $entry->Format, "\n";

            if ($entry->{type} =~ /symlink/) {
                SpewLinkFile($entry->{localpath});
                undef $entry;
            } elsif ($isbinary) {
                SpewBinaryFile($localpath);
                $fUnicodeFile = 1 if $isbinary =~ /unicode/i;
                undef $entry;           # finished with binary files
            }
        } elsif (!$entry) {         # Expected file header
            die "internal error: parsing sd diff output (expecting header)\n".
                "-- perhaps a file does not end in a newline\n$possibleBad"
                unless $line eq "(... files differ ...)\n";
        } elsif ($line =~ /^d/) {   # Lines to delete
            Emit $line;             # Copy to output
        } elsif ($line =~ /^a\d+ (\d+)/) { # lines to add
            Emit $line;
            $copy = $1;             # Number of lines to copy blindly
        } else {
            dprint "barf: $line";
            die "internal error: parsing sd diff output (expecting header or a/d)\ngot $line\n";
        }
    }

    Emit "q\n" if $entry;           # Finish that last diff (if any)

    close(SD);

    # Unlink the temp file again, in case the output was null
    unlink($tempfile), $tempfile = undef if $tempfile;

    die "error: Could not parse output of sd diff\n".
        "-- perhaps a file does not end in a newline\n$possibleBad".
        "-- or you've hit MaxResults -- try specifying files individually\n"
        unless $copy == 0 && $files == $ChangeList->{edit};
}

#
#   Emit the added files.
#

foreach my $entry ($ChangeList->GetAllEntries()) {
    if ($entry->{cmd} eq 'add') {
        vprint "add $entry->{localpath}\n";
        if ($entry->{type} =~ /binary|unicode/) {
            Emit $entry->Format, "\n";
            SpewBinaryFile($entry->{localpath});
        } elsif ($entry->{type} =~ /symlink/) {
            Emit $entry->Format, "\n";
            SpewLinkFile($entry->{localpath});
        } else {
            open(I, $entry->{localpath})
                or die "error: cannot open $entry->{localpath} for reading ($!)\n";
            my @slurp = <I>;
            close(I);
            if (scalar(@slurp) && substr($slurp[$#slurp], -1) ne "\n") {
                $entry->{type} .= "_nonewline";
                $slurp[$#slurp] .= "\n";
            }
            Emit $entry->Format, "\n";
            Emit "a0 ", scalar(@slurp), "\n", @slurp, "q\n";
        }
    } elsif ($entry->{cmd} eq 'delete') {
        vprint "delete $entry->{localpath}\n";
        Emit $entry->Format, "\n";
    }
}

close(O) or die "error: writing ($!)\n";
$main::oCleanup = undef;

if ($main::v && $main::o ne "-") {
    vprint "verifying package $main::o...\n";
    if ($^O =~ /^MSWin(32|64)$/) {
        system $^X, "-Sx", "\"$main::o\"", "-v";
    } else { 
        system $^X, "-x", "$main::o", "-v";
    }
}

RepeatWarnings();

END {
    if ($main::oCleanup) {
        close(O);
        warn "Deleting failed package $main::oCleanup\n";
        unlink $main::oCleanup;
    }
}

__END__
#!/usr/bin/perl -w

BEGIN {
    # augment library path for OTOOLS environment
    if (defined $ENV{"OTOOLS"}) {
        require "$ENV{'OTOOLS'}\\lib\\perl\\otools.pm"; import otools;
    }

    # Convert "use strict 'subs'" to the eval below so we don't
    # barf if the user's @INC is set up wrong.  You'd be surprised
    # how often this happens.
    eval { require strict; import strict 'subs' };
}

require 5.004;
die "Unsupported OS ($^O), sorry.\n" 
    unless ($^O =~ /^MSWin(32|64)$/ or $^O eq 'darwin'); 

sub Usage {
    my $usage = <<'EOM';
NAME

$name - unpack a buddy build package

SYNOPSIS

    $name -? | -h

    $name [-A dir] [-B dir] [-d] [-c changelist] [-f] [-l] [-m from to | -M]
          [-n] [-R resolve-options] [-s] [-T] [-u] [-v] [-W "args"] [-w] [-x]

DESCRIPTION

    Unpack the buddy build generated by a previous $pack.

OPTIONS

    -? or -h

        Displays this help file.

    -A dir

        Directory to use for "after" files.  The directory will remain.
        Must be used in conjunction with -w.

    -B dir

        Directory to use for "before" files.  The directory will remain.
        Must be used in conjunction with -w.

    -d

        Turns on debugging spew.

    -c changelist

        Unpack the package onto the given changelist.  If this option
        is omitted, the default changelist will be used.

    -f

        Unpack even if the changelist is nonempty.

    -l

        List contents of package.

    -m from to

        Unpack (merge) the package into a location possibly different
        from the one it was built from.  "from" and "to" indicate the
        relationship between the source and target depots.  For example,
        if the original package was built from //depot/branch1/... and
        you want to unpack to //depot/branch2/... you would specify

            -m //depot/branch1/ //depot/branch2/

        Note the trailing slashes.  The remapping is a purely textual
        one:  All paths in the package that begin with "from" are
        rewritten to begin with "to", hence the importance of the trailing
        slash to avoid false matches.  If you misspell "from" or "to",
        you are likely to get very strange results.

        The files are unpacked into the current client, which
        need not be enlisted onto the same server that the package
        was generated from.

        It is legal for "from" and "to" to be the same path.  This
        results in merging a delta without moving it.  See the -M
        option below.

        May not be combined with the -s or -w switches.

    -M

        Shorthand for "-m // //", which merges a changelist without
        moving it.

    -n

        Display what would have happened without actually doing
        it.

    -R  resolve-options

        Arbitrary options to pass to "sd resolve3".  For example,
        you could say

            -R -af

        to force automatic mode.  For a list of supported options,
        type

            sd help resolve3

    -s

        Synchronize to the versions of the files that are
        the bases for the changes contained in the package,
        but do not unpack them.

        This is a convenient step to perform separately
        from unpacking because it allows you to perform a
        pre-build to ensure that the build was not broken
        before you unpacked the files in the package.

    -T

        Restore original file timestamps when unpacking.

    -u

        Perform the unpack.  This switch can be combined with
        the -s switch to synchronize and unpack in one step.

        The unpack will fail if the changelist is nonempty.
        Use the "sd change" command to move files in the default
        changelist to a new changelist.  This allows you to use
        "sd revert -c default ..." to undo the unpack.

        To force the unpack even if the changelist is empty,
        pass the -f flag.  Note that doing so will result in the
        unpacked files being added to your changelist,
        which in turn makes reverting the unpack a much more
        cumbersome operation.

    -v

        Verify that the package will produce results
        identical to what's on the machine right now.
        Use this immediately after generating a package as a
        double-check.

    -w

        View contents of packages using windiff (or whatever your
        BBDIFF environment variable refers to). On the Mac, this defaults
        to FileMerge instead of windiff.

    -W "args"

        Pass additional arguments to windiff (or whatever your BBDIFF
        environment variable points to).  For example, you can pass
        you can pass a comment file to windiff with the following switch:

           -W "-c commentfile"

        This flag naturally has no effect if you don't also pass -w.

    -x

        Unpack the files as UNIX-style (LF only) rather than
        Win32-style (CRLF).

    -T

        Preserve the last changed timestamps for all files when
        unpacking.

WARNINGS

    warning: filename merge cancelled by user; skipped

        A file in the package needed to be merged, but you abandoned
        the merge operation ("s" or "q").  The file was left in its original
        state; the changes were not merged in.

    warning: //depot/.../filename not affected by branch mapping; skipped

        The indicated file in the package is not affected by the
        from/to mapping, so it was omitted from the merge.

    warning: filename created as text; Windows doesn't support symlinks
    
        A file in the package is of type symlink, which is not natively 
        supported on Windows. Since Windows sd will sync these as a text
        file, the unpacking will create a similar text file.

ERRORS

    error: sd failed; unpack abandoned

        One of the sd commands necessary to complete the unpack failed.
        The sd error message should have been displayed immediately
        before this message.

    error: cannot find local copy of //depot/.../filename

        The indicated file in the package could not be found on your
        enlistment.  Perhaps you have not included it in your view.

    internal error: cannot parse output of 'sd have'
    internal error: Cannot parse output of 'sd opened'

        There was a problem parsing the output of an sd command.

    error: changelist is not empty; use -f -u to unpack anyway

        The changelist is not empty, so the unpack
        was abandoned.  To force unpacking into a nonempty
        changelist, use the -f switch.

    error: filename is already open on client; to merge, use the -M option

        The specified file is already open.  It must be submitted or
        reverted before the package can be unpacked cleanly.

        Alternatively, you can unpack in "merge" mode, which merges
        the changes in the package with the version on your machine.
        Note that this will DESTROY the version on your machine in the
        process, so back it up (possibly with bbpack) if there's a chance
        the merge will not go well.

    error: adds in this package already exist on client

        The package contains an "add" operation, but the file already
        exists.  It must be ghosted or deleted before the package can
        be unpacked.

    error: files to be edited/deleted do not exist on client

        The package contains an "edit" or "delete" operation, but the
        file does not exist on the client.  Perhaps you have not
        included it in your view.

    error: wrong version of filename on client

        The base version of the file in the package does not match the
        base version on the client.  Use the -s option to synchronize
        to the version in the package.

    error: filename does not match copy in package

        The verification process (-v) failed.

    error: corrupted package

        An internal consistency check on the package has failed.  Either
        it has been corrupted, or there is a bug in the program.

    error: cannot open filename for writing (reason)

        The specified error occurred attempting to open the indicated
        file for writing.

    error: filename: errorstring

        The specified error occurred attempting to open the indicated
        file.

    error: no TEMP directory

        Neither the environment variable TEMP nor TMP could be found.

    error: Too many TEMP### directories

        Unable to create a temporary directory for windiff because there
        are too many already.  Normally, temporary directories are cleaned
        up automatically when the script terminates, but if the script
        terminates abnormally, temporary directories may be left behind
        and need to be cleaned up manually.

    //deport/path/to/file.cpp - must refer to client 'CLIENTNAME'
    error: sd failed; unpack abandoned

        This is an sd error message.  You spelled "depot" wrong ("deport")
        in the -m command line arguments.  As a result, sd thinks you are
        trying to merge with the file "file.cpp" on the enlistment named
        "deport", and sd won't let you check out a file on another person's
        enlistment.

TIPS

    Brain surgery

    $name stores as much state as possible in the depot itself in order
    to keep the package small.  If your server changes its name, you have
    to perform brain surgery on the package.  Load it up into notepad
    and look for the _!_END_!_ line.  A few lines after the _!_END_!_ will
    be a

        Server address: oldserver:portnumber

    Change the server address to refer to the new server and new port
    number.

    NOTE!  Use Notepad and not "My Favorite Editor" because who knows
    what "My Favorite Editor" does to tabs and trailing spaces and
    that sort of thing. (On the Mac, use Xcode or BBEdit.)

REMARKS

    4NT users need to type

        perl -Sx $name.cmd

    instead of just $name.

ENVIRONMENT

    BBDIFF

        The name of the diff program to use.  If not defined, the
        SDDIFF variable is used to obtain the name of the file difference
        program.  If neither is defined, then "windiff" is used.

    BBUNPACKDEFCMD

        The default command to execute if no command line options are
        specified.  If not defined, then an error message is displayed.

        For example, you might set BBUNPACKDEFCMD=-w to make the default
        action when running a package to be to view the contents via
        windiff.

    Since $name runs sd internally, all the SD environment variables
    also apply.

BUGS

    Several error messages leak out when you unpack an sd add.
    (This is happening while verifying that the file about to be
    added hasn't already been added.)

    If the package contains an "add" command and the file exists
    on the client but is not under source control, the file is overwritten
    without warning.

    There are almost certainly other bugs in this script somewhere.

VERSION

    The package was generated by version $packver of $pack.

EOM
    $usage =~ s/\$name/$main::name/g;
    $usage =~ s/\$pack/$main::pack/g;

    # prevent false positives when searching for the magic cookie
    $usage =~ s/_!_/__/g;
    print $usage;
}

sub dprint {
    print STDERR "# ", @_, "\n" if $main::d;
}

#
#   $action is optional prefix for printing.
#   $sharp says whether or not revisions should be kept.
#   $ary is a ref to an array of [ $file, $rev ].
#
#   We always convert the depot paths to local paths for perf.
#   (It works around a perf bug in older versions of sds.)
#
#   Returns a ref to an array of strings to pass to -x.

sub sdarg {
    my ($action, $sharp, $ary) = @_;
    my @out = ();
    my %files;
    my $rc = "";

    for my $file (@$ary) {
        my $depot = $file->[0];
        $files{lc $depot} = $file;
        push(@out, "$depot\n");
    }

    # Now convert the results into a list of local paths.  Anything
    # that succeeds, edit it in the %files.  Anything that fails to map
    # gets left alone, and sd will generate the real error later.

    my $tempfile = CreateTempFile(@out);
    my $curDepot = undef;
    for my $line (`sd -x $tempfile -s where -T _`) {
        if ($line =~ m|^info:|) {
            $curDepot = undef;
        } elsif ($line =~ m|^info1: depotFile (.*)$|) {
            $curDepot = $1;
        } elsif ($line =~ m|^info1: path (.*)$|) {
            my $curFile = $files{lc $curDepot};
            if ($curFile) {
                $curFile->[0] = $1;
                dprint "$curDepot -> $1";
            }
            $curDepot = undef;
        }
    }
    unlink $tempfile;

    # Now rebuild the results based on the localized paths.
    @out = ();
    for $file (values %files) {
        push(@out, $file->[0]);
        push(@out, "#" . $file->[1]) if $sharp;
        push(@out, "\n");
    }

    \@out;
}

#
#   $action is a command ("sync#", "edit", "add" and "delete")
#
#   The revision number is stripped off the file specification
#   unless the action itself ends in a # (namely, sync#).
#
#   $ary is a ref to an array of [ $file, $rev ].

sub sdaction {
    my ($action, $ary) = @_;
    my $sharp = $action =~ s/#$//;

    if ($#$ary >= 0) {

        my $args = sdarg($action, $sharp, $ary);

        unless ($main::n) {
            my $error = 0;
            my $tempfile = CreateTempFile(@$args);
            if (open(SD, "sd -x $tempfile -s $action |"))
            {
                my $line;
                while ($line = <SD>) {
                    if ($line =~ /^(\S+): /) {
                        $error = 1 if $1 eq 'error';
                        print $' unless $1 eq 'exit';
                    }
                }
                close(SD);
            }
            unlink $tempfile;
            die "error: sd failed; unpack abandoned\n" if $error;
        }
    }
}

sub slurpfile {
    my ($file, $type) = @_;
    my @file;
    if ($type =~ /symlink/) {
        @file = (readlink $file) or die "error: cannot open symlink $file ($!)\n";
    } elsif ($type =~ /binary|unicode/) {
        open(B, $file) or die "error: cannot open $file for reading ($!)\n";
        binmode(B);
        local($/);
        push(@file, <B>);
        close(B);
    } else {
        open(I, $file) or die "error: cannot open $file for reading ($!)\n";
        @file = <I>;
        close(I);
    }
    @file;
}

sub spewfile {
    my ($file, $ary, $type) = @_;

    # Maybe the parent directory hasn't been created yet
    my $dir = $file;
    $dir =~ s/\\/\//g;
    if ($dir =~ s/[^\/]+$//) {
        if ($^O =~ /^MSWin(32|64)$/)
        {
            system "md \"$dir\"" unless -e $dir; # let cmd.exe do the hard work
        }
        else
        {
            system "mkdir -p \"$dir\"" unless -e $dir; # let mkdir do the hard work
        }
        if (!-d $dir) {
            die "error: $dir exists and is not a directory\n" if (-e $dir);
            die "error: could not create directory $dir ($!)\n";
        }
    }

    if ($type =~ /symlink/) {
        unlink $file;
        if ($^O =~ /^MSWin(32|64)$/)
        {
            warn "warning: $file created as text; Windows doesn't support symlinks\n";
            open(O, ">$file") or die "error: cannot open $file for writing ($!)\n";
            print O ${$ary}[0] . "\n";
        }
        else
        {
            symlink(${$ary}[0], $file) or die "error: cannot create symlink $file ($!)\n";
        }
    } else {    
        open(O, ">$file") or die "error: cannot open $file for writing ($!)\n";
        if ($main::x || $type =~ /binary|unicode/) {
            binmode(O);
        }
        print O @$ary;
    }
    close(O);
    chmod 0755, $file if ($type =~ /^x/ or $type =~ /\+x/);
}

sub GetUniqueName {
    my $name = shift;
    if ($main::m) {
        $name = "tmp";          # prefix is wrong when remapping
    } else {
        $name =~ s,^[/\\]*,,;   # clean out leading slashes
        $name = substr($name, length($main::CommonPrefix));
        $name =~ s,^[/\\]*,,;   # clean out leading slashes again
    }

    if (defined($main::UniqueNames{lc $name}))
    {
        my $i = 1;
        $i++ while $main::UniqueNames{lc "$name$i"};
        $name .= $i;
    }
    $main::UniqueNames{lc $name} = 1;
    $name;
}

sub CreateTempFile {
    my $TEMP = $ENV{"TEMP"} || $ENV{"TMP"} || "/tmp";
    die "error: no TEMP directory" unless -d $TEMP;
    $TEMP =~ s/\\$//;     # avoid the \\ problem

    $tempfile = "$TEMP/bbpack.$$";
    open(T, ">$tempfile") || die "error: Cannot create $tempfile\n";
    my $success = print T @_;
    $success = close(T) && $success;
    unlink $tempfile, die "error: writing $tempfile ($!)\n" unless $success;
    $tempfile;
}

sub Remap {
    my $path = shift;
    if ($path =~ m#^\Q$main::fromDepot\E#i) {
        substr($path, $[, length($main::fromDepot)) = $main::toDepot;
    }
    $path;
}

#
#   $depotpath, $rev is the file to be edited/added.
#   $cmd is "edit" or "add" (indicates where basefile comes from)
#

sub ApplyEdit {
    my ($depotpath, $rev, $cmd, $type, $atime, $mtime) = @_;
    my $destpath = $depotpath;
    my $destfile;
    my ($where, $file);

    if ($main::w) {
        $file = $depotpath; # for the purpose of GetUniqueName
    } else {
        $destpath = Remap($depotpath) if $main::m;
        dprint "$depotpath -> $destpath" if $main::m;
        local($/) = ""; # "sd where -T" uses paragraphs
        foreach $line (`sd where -T _ \"$destpath\" 2>&1`) {
            undef $where, next if $line =~ m|^\.\.\. unmap|m;
            $where = $1 if $line =~ m|^\.\.\. path (.+)|m;
        }
        die "error: cannot find local copy of $destpath\n" unless $where;
        $destfile = $file = $where;
    }
    my @file;
    my $bias = -1;  # perl uses zero-based arrays but diff uses 1-based line numbers

    if ($cmd eq 'add') {
        @file = ();
        $file = $destfile if $main::m;
    } elsif ($cmd eq 'edit') {
        my $src = $file;
        if ($main::v || $main::w || $main::m) {
            dprint "sd$main::ExtraFlags print -q \"$depotpath#$rev\"";
            $src = "sd$main::ExtraFlags print -q \"$depotpath#$rev\"|";
        }
        @file = slurpfile($src, $type);
    } elsif ($cmd eq 'delete') {
        if ($main::w) {
            dprint "sd$main::ExtraFlags print -q \"$depotpath#$rev\"";
            @file = slurpfile("sd$main::ExtraFlags print -q \"$depotpath#$rev\"|", $type);
        } else {
            @file = ();
        }
    }

    my $unique;
    my $whichSlash = ($^O =~ /^MSWin(32|64)$/ ? '\\' : '/');
    if ($main::w || ($main::m && $cmd eq "edit")) { # Write the original, set up for new
        $unique = GetUniqueName($file);
        spewfile("$main::BeforeDir$whichSlash$unique", \@file, $type) unless $cmd eq 'add';
        $file = "$main::AfterDir$whichSlash$unique";
    }

    if ($cmd ne 'delete') {
        # now read from <DATA> and apply the edits.
        if ($type =~ /binary|unicode|symlink/) {
            local($/) = "";
            @file = (unpack("u", scalar(<DATA>)));
        } else {
            while (defined ($line = <DATA>) && $line ne "q\n") {
                if ($line =~ /^a(\d+) (\d+)/) {
                    my @added = ();
                    my $count = $2;
                    while ($count--) {
                        push(@added, scalar(<DATA>));
                    }
                    splice(@file, $1 + $bias + 1, 0, @added); # +1 because it's "add", not "insert"
                    $bias += $2;
                } elsif ($line =~ /^d(\d+) (\d+)/) {
                    splice(@file, $1 + $bias, $2);
                    $bias -= $2;
                } else {
                    die "error: corrupted package trying to unpack $depotpath\n".
                        "       expected a/d/q but got\n".
                        "           $line";
                }
            }

            if ($type =~ /_nonewline/) {
                chomp($file[$#file]);
            }
        }

        if ($main::v) {
            my @file2 = slurpfile($file, $type);
            join("", @file) eq join("", @file2) or
                die "error: $file does not match copy in package\n";
            print "$file is okay\n";
        } else {
            spewfile($file, \@file, $type);
        }

        if ($cmd eq "edit" && $main::m) {
            dprint "sd resolve3 $main::R \"$main::BeforeDir$whichSlash$unique\" \"$main::AfterDir$whichSlash$unique\" \"$destfile\" \"$destfile.out\"";
            system("sd resolve3 $main::R \"$main::BeforeDir$whichSlash$unique\" \"$main::AfterDir$whichSlash$unique\" \"$destfile\" \"$destfile.out\"");
            if (-e "$destfile.out") {
                unlink $destfile;
                rename "$destfile.out", $destfile;
                my $mode = ($type =~ /^x/ or $type =~ /\+x/) ? 0744 : 0644;
                chmod $mode, $destfile;
            } else {
                warn "warning: $destfile merge cancelled by user; skipped\n";
            }
            unlink "$main::BeforeDir$whichSlash$unique";
            unlink "$main::AfterDir$whichSlash$unique";
        }

        if ($main::T && $atime && $mtime) {
            utime $atime, $mtime, $destfile;
        }
    }
}

sub IsDirectoryEmpty {
    my $dir = shift;
    my $empty = 1;
    if (opendir(D, $dir)) {
        while ($file = readdir(D)) {
            $empty = 0, last if $file ne '.' && $file ne '..';
        }
        closedir(D);
    } else {
        $empty = 0;         # Wacky directory, pretend nonempty so we skip it
    }
    $empty;
}

$main::NextUniqueDir = 0;

sub GetNewTempDir {
    my $TEMP = "";
    if ($^O =~ /^MSWin(32|64)$/)
    {
        my $TEMP = $ENV{"TEMP"} || $ENV{"TMP"};
        die "error: no TEMP directory" unless $TEMP;

        $TEMP =~ s/\\$//;     # avoid the \\ problem

        $TEMP .= "\\bbtmp";
    }
    else
    {
        $TEMP = '/tmp/bbtmp';
    }

    # Look for suitable "before" and "after" directories; we'll
    # call them "bbtmp###".


    while ($main::NextUniqueDir++ < 1000) {
        my $try = "$TEMP$main::NextUniqueDir";
        if (!-e $try && mkdir($try, 0777)) {
            return $try;
        }
        if (-d _ && IsDirectoryEmpty($try)) {
            return $try;
        }
    }
    die "error: Too many ${TEMP}### directories\n";
}

sub CleanDir {
    my $dir = shift;
    if (defined($dir) && -e $dir) {
        if ($^O =~ /^MSWin(32|64)$/)
        {
            system "rd /q /s $dir";
        }
        else
        {
            system "rm -rf '$dir'";
        }
    }
}

sub AccumulateCommonPrefix {
    my $file = "/" . lc shift;

    # Remove filename component
    while ($file =~ s,[/\\][^/\\]*$,,) {
        last unless defined $main::CommonPrefix;
        last if substr($main::CommonPrefix, 0, length($file)) eq $file;
    }

    $main::CommonPrefix = $file;
}

#
#   Okay, now initialize our globals.
#

$main::name = $0;
$main::name =~ s/.*[\/\\:]//;

$main::A = 0;
$main::B = 0;
$main::c = "default";
$main::d = 0;
$main::f = 0;
$main::l = 0;
$main::m = 0;
$main::n = 0;
$main::R = "";
$main::s = 0;
$main::T = 0;
$main::u = 0;
$main::v = 0;
$main::W = undef;
$main::w = 0;
$main::x = 0;
$main::anyChanges = 0;

$main::nul = ($^O eq 'darwin') ? '2>/dev/null' : '2>nul';

$main::BeforeDir = undef;
$main::AfterDir  = undef;
%main::UniqueNames = ("" => 1); # preinit to avoid blank name
$main::ExtraFlags = "";
$main::fromDepot = undef;
$main::toDepot = undef;
$main::CommonPrefix = undef;

if ($^O =~ /^MSWin(32|64)$/)
{
    #
    #   NASTY HACK TO WORK AROUND PERL BUG IN <DATA> HANDLING.
    #   Reopen ourselves and advance to the raw data.
    #
    open(DATA, $0);
    0 until scalar(<DATA>) eq "__END__\n";
}

my %PackerProperties;

{
    binmode(DATA, ":crlf");
    my $line;
    while (defined ($line = <DATA>) && $line =~ /(.*?): (.*)/) {
        if ($1 eq "Change Description") {
            $PackerProperties{$1} .= $2."\n";
        } else {
            $PackerProperties{$1} = $2;
        }
    }
    $main::pack = delete $PackerProperties{Packager};
    die "error: corrupted package, end of line expected\n" unless $line eq "\n" && $main::pack;
    die "error: your version of perl doesn't support lines longer than 256 characters\n"
        unless $PackerProperties{"PerlSniffTest"} eq "." x 256;
}

#   If there is no command line and there is a BBUNPACKDEFCMD, use that
#   variable instead.

if ($#ARGV < 0 && defined $ENV{"BBUNPACKDEFCMD"}) {
    my $cmd = $ENV{"BBUNPACKDEFCMD"};
    $cmd =~ s/^\s+//;
    while ($cmd =~ s/^\s*(?:"([^"]*)"|([^"]\S*))\s*//) {
        push(@ARGV, $+);
    }
}

while ($#ARGV >= 0 && $ARGV[0] =~ /^-/) {
    my $switch = shift;
    if ($switch eq '-d') {
        $main::d++;
    } elsif ($switch eq '-f') {
        $main::f++;
    } elsif ($switch eq '-l') {
        $main::l++;
    } elsif ($switch eq '-m') {
        $main::m++;
        $main::fromDepot = shift;
        $main::toDepot = shift;

        if ($main::fromDepot !~ m#^//# ||
            $main::toDepot !~ m#^//#) {
            die "-m must be followed by two depot prefixes; type $name -? for help\n";
        }

    } elsif ($switch eq '-M') {
        $main::m++;
        $main::fromDepot = $main::toDepot = '/';
    } elsif ($switch eq '-c') {
        $main::c = shift;

        if ($main::c !~ m#^[0-9]#) {
            die "-c must be followed by a changelist number; type $name -? for help\n";
        }

    } elsif ($switch eq '-A') {
        die "only one instance of -A allowed; type $name -? for help\n" if $main::A;
        $main::A++;
        $main::AfterDir = shift || die "-A requires an argument; type $name -? for help\n";
    } elsif ($switch eq '-B') {
        die "only one instance of -B allowed; type $name -? for help\n" if $main::B;
        $main::B++;
        $main::BeforeDir = shift || die "-B requires an argument; type $name -? for help\n";
    } elsif ($switch eq '-n') {
        $main::n++;
    } elsif ($switch eq '-R') {
        $main::R = shift;
    } elsif ($switch eq '-s') {
        $main::s++;
    } elsif ($switch eq '-u') {
        $main::u++;
    } elsif ($switch eq '-v') {
        $main::v++;
    } elsif ($switch eq '-w') {
        $main::w++;
    } elsif ($switch eq '-x') {
        $main::x++;
    } elsif ($switch eq '-T') {
        $main::T++;
    } elsif ($switch eq '-W') {
        die "Cannot specify -W more than once\n" if defined $main::W;
        $main::W = shift || die "-W requires an argument type $name -? for help\n";
    } elsif ($switch eq '-?') {
        Usage(); exit 1;
    } else {
        die "Invalid command line switch; type $name -? for help\n";
    }
}

# Should be no command line options
die "Invalid command line; type $main::name -? for help\n" if $#ARGV >= 0;

die "Must specify an action; type -? for help\n"
    unless $main::l || $main::s || $main::u || $main::v || $main::w;

# suppress -w (presumably from registered .bpk extension)
# if other actions found
$main::w = 0
        if $main::l || $main::s || $main::u || $main::v;


die "Cannot combine -m with -s\n" if $main::m && $main::s;
die "Cannot combine -m with -w\n" if $main::m && $main::w;

#
#   -l wants some meta-information about the package.
#
if ($main::l) {
    my $key;
    foreach $key (split(/,/, "Comment,Client name,User name,Date,Change Description")) {
        #
        # Make sure to print blank properties for backwards compatability for
        # anyone who parses the output.
        #
        if ($PackerProperties{$key}) {
            map { print "$key: $_\n"; } split(/\n/, $PackerProperties{$key});
        } else {
            my $value = $PackerProperties{$key};
            $value = '' if not defined $value;
            print "$key: $value\n";
        }
    }
    print "\n";
}

#
#   See which files are open on the client.  This also establishes whether
#   the server is up and the user has proper permissions.
#
my %OpenedFiles;

if ($main::s || $main::u) {
    # Intentionally let errors through to stderr
    # Use -s to suppress stderr if no files are opened
    foreach my $line (`sd -s opened -c $main::c`) {
        next if $line =~ m,^warning: , || $line =~ m,^exit: ,;
        next if $line =~ m!^(error|warning): File\(s\) not opened !;
        $line =~ m,^info: (//.*?)#(\d+|none),
            or die "error: Cannot parse output of 'sd opened -c $main::c'\n";
        $OpenedFiles{$1} = 1;
        dprint "opened $1#$2";
        $main::anyChanges = 1 if $' =~ /$main::c/;
    }
}

die "error: changelist $main::c is not empty; use -f -u to unpack anyway\n"
    if $main::anyChanges && $main::u && !$main::f;

#
#   The -w and -m options require us to set up some directories for unpacking.
#
if ($main::w || $main::m)
{
    $main::BeforeDir = GetNewTempDir() unless defined $main::BeforeDir;
    $main::AfterDir  = GetNewTempDir() unless defined $main::AfterDir;
    $main::ExtraFlags = " -p $PackerProperties{'Server address'}";
}

#
#   Go through each file in the package and perform an appropriate
#   action on it.
#

{
    my (@sync, @edit, @add, @delete);

    my $line;
    {
        while (defined ($line = <DATA>) && $line =~ m|^(//.*?)#(\d+) (\S+) (\S+)|) {
    
            #   $1 = depot path
            #   $2 = rev
            #   $3 = action
            #   $4 = filetype (not currently used)
    
            if ($main::l) {
                print $line;
            }
    
            #   If sync'ing or unpacking, then the file had better not be open
            #   since we're the ones who are going to open it.
    
            die "error: $1 is already open on client; to merge, use the -M option\n"
                if defined $OpenedFiles{$1} && ($main::s || ($main::u && !$main::m));
    
            #   If sync'ing, add to list of files that need to be sync'd.
            #
            #   If unpacking, then add to the appropriate list so we know
            #   how to prepare the file for action.
    
            if ($main::s) {
                push(@sync, [ $1, $3 eq 'add' ? 'none' : $2 ]);
            }
            if ($main::u) {
    
                my $path = $1;
                if ($main::m) {
                    $path = Remap($1);
                }
    
                if ($path) {
                    if ($3 eq 'edit') {
                        push(@edit, [ $path, $2 ]);
                    } elsif ($3 eq 'add') {
                        push(@add, [ $path, $2 ]);
                    } elsif ($3 eq 'delete') {
                        push(@delete, [ $path, $2 ]);
                    } else {
                        die "error: corrupted package, operation $3 unrecongized\n";
                    }
                }
            }
    
            AccumulateCommonPrefix($1);
    
        }
    }
    die "error: corrupted package, bad format on $line\n" unless $line eq "\n";

    $main::CommonPrefix =~ s,^[/\\]+,,; # clean off leading slashes

    if ($main::s || $main::u) {

        #
        #   Make sure that no files being added currently exist.
        #
        if ($#add >= 0) {
            my $args = sdarg(undef, undef, \@add);
            my $tempfile = CreateTempFile(@$args);
            if (`sd -x $tempfile have $main::nul`) {
                unlink $tempfile;
                die "error: adds in this package already exist on client\n";
            }
            unlink $tempfile;
        }

        #
        #   Make sure that files being edited are the correct versions.
        #
        if (($#edit >= 0 || $#delete >= 0) && !$main::s && !$main::m) {
            my @have = (@edit, @delete);
            my %have;
            my $file;
            my $args = sdarg(undef, undef, \@have);
            my $tempfile = CreateTempFile(@$args);
            dprint "sd have @$args";
            for $file (`sd -x $tempfile have`) {
                $file =~ m|(//.*?)#(\d+) - (.*)| or die "error: parsing output of 'sd have'\n";
                dprint "have $1#$2 - $3";
                #
                #    Store the have under both the depot path and the local path.
                #
                $have{lc $1} = $2;
                $have{lc $3} = $2;
            }
            unlink $tempfile;
            die "error: files to be edited/deleted do not exist on client\n" if $?;
            for $file (@have) {
                die "error: wrong version of $file->[0] on client\n"
                    if $have{lc $file->[0]} ne $file->[1];
            }
        }

        sdaction("sync#", \@sync);
        sdaction("edit -c $main::c", \@edit);
        # Do not do the adds yet; wait until after the edits have been applied
        sdaction("delete -c $main::c", \@delete);
    }

    #
    #   Now go extract the actual files.
    #
    if (!$main::n && ($main::u || $main::v || $main::w)) {
        my $line;
        # " *" because some editors trim trailing spaces
        while (defined ($line = <DATA>) && $line =~ m|^(//.*?)#(\d+) (\S+) (\S+) *(\d*) *(\d*)|) {
            ApplyEdit($1, $2, $3, $4, $5, $6);
        }
    }

    # Okay, now do the adds now that the output files have been created
    sdaction("add -c $main::c", \@add);
}

if ($main::w) {
    my $windiff = $ENV{"BBDIFF"} || $ENV{"SDDIFF"} || ($^O =~ /^MSWin(32|64)$/ ? 'windiff' : undef);
    if (not defined $windiff) {
        system('/Developer/Applications/Utilities/FileMerge.app/Contents/MacOS/FileMerge',
            '-left', $main::BeforeDir, '-right', $main::AfterDir);
    } else {
        $main::W = '' if not defined $main::W;
        system("$windiff $main::W \"$main::BeforeDir\" \"$main::AfterDir\"");
    }
}

CleanDir($main::BeforeDir) unless $main::B;
CleanDir($main::AfterDir) unless $main::A;

__END__
