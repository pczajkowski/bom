# BOM

I've written it for fun and because BOM is still a valid problem in l10n world. It's simple and relies only on standard libraries, so should work pretty much everywhere.

It contains simple test which you can run by:

	make test

I've also added simple wrapper, so you can use it as executable:

	Usage:
	./bomToolkit <filePath> c - to check for BOM.
	./bomToolkit <filePath> r - to remove BOM.
	./bomToolkit <filePath> a - to add BOM.

It's 22 times faster than similar one I've written in C#, so either C is faster at that or I've written it better:) Enjoy!

***As always, you can use it as you want, but I give you no warranty.***
