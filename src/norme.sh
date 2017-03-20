#!/bin/bash
# file=`ls`
file=$1
SIZE_HEADER=12

sed -i  's/^  /	/g'  $file; #remplace 2 espace par des tabulation ne doit pas prendre le header

sed -i  's/return;/return ;/g' $file; #remplace return; par return ;

sed -i 's/^ //g' $file; #delete space before the end of comment

# # sed -i '/^$/d' $file; #delet empty line
sed -i '/^\*\//a\ ' $file; #append a line with a space after the end of a comment

sed -i  's/[ \t]*$//' $file; #efface les espaces en fin de ligne

sed -i 's/ ;/;/g' $file; #delete space before ;

sed -i 's/( /(/g' $file; #delete space after (

sed -i 's/ )/)/g' $file; #delete space before )

sed -i ''$SIZE_HEADER',$ s/  / /g' $file; #replace '  ' by ' '

sed -i ':a;N;N;$!ba;s|/\*\n|\n/\*\n|g' $file; #add space before comment

sed -i ':a;N;$!ba;s/\n\n\n/\n\n/g' $file; #remplace 3 \n par 2

# # add a tab between type and var#
sed -i 's/\(\tint \)\(.*;\)/\tint\t\t\t\t\2/g' $file;
sed -i 's/\(\tchar \)\(.*;\)/\tchar\t\t\t\2/g' $file;
sed -i 's/\(\tvoid \)\(.*;\)/\tvoid\t\t\t\2/g' $file;
sed -i 's/\(\tpid_t \)\(.*;\)/\tpid_t\t\t\t\2/g' $file;
sed -i 's/\(\tt_arr \)\(.*;\)/\tt_arr\t\t\t\2/g' $file;
sed -i 's/\(\tt_cursor \)\(.*;\)/\tt_cursor\t\t\2/g' $file;
sed -i 's/\(\tt_fork \)\(.*;\)/\tt_fork\t\t\t\2/g' $file;
sed -i 's/\(\tt_kval \)\(.*;\)/\tt_kval\t\t\t\2/g' $file;
sed -i 's/\(\tstruct \)\(.*;\)/\tstruct\t\t\t\2/g' $file;
sed -i 's/\(\tt_tube \)\(.*;\)/\tt_tube\t\t\t\2/g' $file;
sed -i 's/\(\tt_env \)\(.*;\)/\tt_env\t\t\t\2/g' $file;
sed -i 's/\(\tt_arr_fd \)\(.*;\)/\tt_arr_fd\t\t\2/g' $file;
sed -i 's/\(\tt_tab_tube \)\(.*;\)/\tt_tab_tube\t\t\2/g' $file;
sed -i 's/\(\tt_list_arr \)\(.*;\)/\tt_list_arr\t\t\2/g' $file;
sed -i 's/\(\tt_cmd_line \)\(.*;\)/\tt_cmd_line\t\t\2/g' $file;
sed -i 's/\(\tunsigned char \)\(.*;\)/\tunsigned char\t\2/g' $file;
# # 								 #

sed -i 's/int f/int\tf/g' $file; # add \t for prototype function

sed -i 's/^\* /\** /g' $file; # format comment * -> **

sed -i 's/\t /\t\t/g' $file;
sed -i 's/\t\t /\t\t\t/g' $file;
sed -i 's/\t /\t\t/g' $file;
