README for TAs

Preliminaries:
Github repo containing the data I used: https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/UniversityWebsite/comp3311_asm4data

I used the same dataset as in Assignment 3, but changed some of the text files via 3311_load_data.ipynb to fully match the Assignment 3 solution.
** In premium.csv, I changed zhouguanyu -> zhouguanyu24 (this was an error in 30 Mar Assignment 3 dataset)

Tables were created using the file: 3311_asm4.sql
The C# code was written based off SQL queries I tested in 3311_asm4_queries.sql

The tables were then populated in the following order in Oracle SQLDeveloper (I did not generate DDL however):
Accounts -> CastMember -> Free -> Premium -> Friends -> Video -> Watches -> Tags -> TVShow -> Movie -> Playlist -> Acts

Queries:
1. Find all movies with the input tag. (e.g., input ‘Comedy’, and the website would show all movies with the tag ‘Comedy’)
2. Find all accounts registered between input time intervals. (e.g., input ‘2011-01-01’ and ‘2015-01-01’)
3. Find the movie with selected cast member that has been watch the most times. (e.g., input ‘Chris Evans’)
4. Find all accounts where the owner is older than an input age (Assume the current date is ‘2022-05-01’).
5. Find all playlists that do not contain a product that aired after an input year. (e.g., input ‘2014’)
6. Add a function to create new users. (e.g., input username, name, birthdate, and whether it is a premium account on the website, then an account would be created)
7. Add a function to delete users. (e.g., input username and then a user deleted)
8. Add a button that shows all users after click.



How to use:

When launching the website, there should be 3 dropdown menus in the top sidebar. Only use the 3rd dropdown menu. There is 1 page for each question (Q1-Q8) asked in Assignment 4, and the codes are in ~/A4/QX.aspx where X in {1, ..., 8}.

The codes called in QX.aspx.cs are additional functions added to UniversityDB.cs.

At any page Q1-Q8, enter the input in the necessary fields and press the button. Empty input always rejected. Otherwise, if the inputs are valid, the results are displayed. Otherwise, the rejected input causes an error message to show up on the website.

Q1: Takes as input a string 'tag'. No check, input always assumed to be valid (if not empty).
>> (ex. 'Fantasy')
Q2: Takes as input two strings 'date1' and 'date2', both of which must be strings in the form YYYY-MM-DD (dates). If not true, reject input. Also, 'date1' and 'date2' are checked to see if 'date1' < 'date2'. If not true, rejects input.
>> (ex. date1='2011-10-02', date2='2013-04-12')
Q3: Takes as input a string 'cast_name'. No check, input always assumed to be valid (if not empty).
>> (ex. 'Chris Evans')
Q4: Takes as input a string 'age', casts it to integer. Check to ensure it is positive numeric, and reject input if not.
>> (ex. '44')
Q5: Takes as input a string 'year'. We check to ensure it is at most 4 digits long and numeric, and reject the input if not.
>> (ex. '2014')
Q6: Takes as input 5 strings 'username', 'name', 'birthdate', 'email', 'isPremium'. We check to ensure 'isPremium' is either '0' (free) or '1' (premium). 'birthdate' must also be a date in the form YYYY-MM-DD. 'name' is always assumed to be valid as long as not empty. 'username' and 'email' must be unique. If all of the above satisfied, add the tuple to 'Account' relation. Also add it to 'Free' or 'Premium' depending on the value of 'isPremium'. Otherwise don't do anything and show error message.
>> (ex. 'lizardman', 'Mark Zuckerberg', '1996-05-26', 'zucc@meta.com', '1')
Q7: Takes as input a string 'username'. We check to ensure the username exists in the Accounts.username. If not, return error message and do nothing. Else delete the tuple in Account whose PK is this username. By delete cascade constraint we imposed, the corresponding FK in Free/Premium referencing this username will also be deleted.
>> (ex. 'mondoduplantis')
Q8: No input. Basically just returns all records in the 'Account' relation upon pressing the button.

