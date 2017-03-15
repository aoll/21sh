#!/bin/bash
file=$1
sed -i  's/^  /	/g'  $file; #remplace 2 espace par des tabulation ne doit pas prendre le header

sed -i  's/return;/return ;/g' $file; #remplace return; par return ;

sed -i 's/^ //g' $file; #delete space before the end of comment

# # sed -i '/^$/d' $file; #delet empty line
sed -i '/^*\//a\ ' $file; #append a line with a space after the end of a comment

sed -i  's/[ \t]*$//' $file; #efface les espaces en fin de ligne

sed -i 's/ ;/;/g' $file; #delete space before ;

sed -i 's/( /(/g' $file #delete space after (

sed -i 's/ )/)/g' $file #delete space before )

sed -i 's/  / /g' $file #replace '  ' by ' '

sed -i ':a;N;N;$!ba;s|/\*\n|\n/\*\n|g' $file; #add space before comment

sed -i ':a;N;$!ba;s/\n\n\n/\n\n/g' $file; #remplace 3 \n par 2
