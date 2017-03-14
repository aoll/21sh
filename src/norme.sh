#!/bin/bash
file=$1
sed -i .back  '12,1000s/  /	/g'  $file #remplace 2 espace par des tabulation ne doit pas prendre le header
#perl -p -i -e  's/[ \t]*$//' $file efface les espaces en fin de ligne
#perl -p -i -e 's/return;/return ;/g' $file #remplace return; par return ;

