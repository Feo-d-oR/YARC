===========================================
================ CHANGELOG ================
===========================================

---------------- v0.3.5b ------------------
Added->Setting->Limitation for orders table
Modified->Search in orders table->Search executed only after button or return pressed
Modified->Suppliers catalog->Fields set expanded
Added->Suppliers catalog->Search

---------------- v0.3.4b ------------------
Some nasty typos in SQL queries fixed
Passwords now kinda encrypted :) (Using SimpleCrypt by Andre Somers)
Separate UI for various roles
Users management (in Employees catalog), default login and password: "admin"
"Permissions" settings editing for works and spares
For spare parts: suppliers, buying price and quantity added

---------------- v0.3.3b ------------------
"Regular" field in "Customers"
"New order by previous customer" feature
Search for regular customers in "New order"
Custom columns in main window
Added "Notify date"
Default employees and order state options

---------------- v0.3.2b ------------------
Fixed "Work report" editing
Fixed salary calculation

---------------- v0.3.1b ------------------
Complete retranslation
DBTool improvements
UI improvements
Various bugfixes
Update to QtRpt 1.5.3

----------------- v0.3 --------------------
Added handwritten documents support
Added salaries accounting
Filtration in comboboxes
Global database operations moved to standalone utility "DBTool"
English help
Printable forms examples translated to english
Some improvements, some fixes...

---------------- v0.2b --------------------
Fixed reports editing
Various UI improvements
Added MySQL user creation
Added help in Russian

---------------- v0.2a --------------------
Added diagnosis processing
Added translation support
Some fixes

===========================================
================= README ==================
===========================================

Dependencies for Qt5 in Ubuntu:
Until someone (maybe me) build packages you should install them manually :(

libqt5printsupport5
libqt5widgets5
libqt5sql5
libqt5sql5-mysql
libqt5script5
libqt5network5
libqt5xml5
libqt5gui5
libqt5core5a
