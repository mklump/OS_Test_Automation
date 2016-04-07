__________
ReadMe.txt
__________

placefil.tst contains an updated version of the SKUDiff section of the placefil.tst in the Shelltest root folder, this must be updated for the files to be placed properly.

Most test code and process documentation, as well as backups of WTT data can be found in the 'TestDocs' folder.

'Archive' is old versions of test, pre-source depot checkins, kept for reference, it's out of data, and discardable.

The 'lib' and 'inc' folders, as well as the 'sources.inc' file are shared by all tests.

'lib' should be first in 'dirs' file, so that it gets built before the tests that depend on it.

All other folders should be listed alphabetically in 'dirs'