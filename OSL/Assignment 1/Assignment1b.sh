#!/bin/sh

create()
{
	echo "Enter the address book name"
	read "ab"
	
	res=`ls | grep $ab | wc -w`
	
	if [ $res -gt 0 ]
	then 
		echo "Error! File is already existing!"
	else
		touch $ab
	fi


}

display()
{
	echo "Enter the address book name to display"
	read "ab"
	
	res=`ls | grep $ab | wc -w`
	
	if [ $res -gt 0 ]
	then 
		cat $ab
	else
		echo "Error! File is not existing!"
	fi


}

insert()
{
	echo "Enter the address book name to display"
	read "ab"
	
	res= `ls | grep $ab | wc -w`
	
	if [ $res -gt 0 ]
	then 
		echo "Enter email"
		read email
		#check email is present in address book or not
		len= `cat $ab | grep $email | wc -w`	
		if [ $len -gt 0 ]
		then 
			echo " Error : Email already existing"
		else 
			echo "Enter First name, Last name, Mobile number"
			read fname lname mobile
			
			record= `echo $fname $lname $email $mobile` 
			echo $record >> $ab
			echo "Record inserted!"
		fi
	else
		echo "Error! File is not existing!"
	fi
}

modify()
{
	echo "Enter the address book name to display"
	read "ab"
	
	res = `ls | grep $ab | wc -w`
	
	if [$res -gt 0]
	then 
		echo "Enter email"
		read email
		#check email is present in address book or not
		len= `cat $ab | grep $email | wc -w`	
		if [ $len -gt 0 ]
		then 
			echo "Enter Modified first name, last name, mobile"
			read fname lname mobile
			new= `echo $fname $lname $email $mobile`
			old= `cat $ab | grep $email`
			
			
			echo "Old record: $old"
			echo "New Record: $new"
			
			sed -i s/"$old"/"$new"/g $ab
			echo "Record Modified!"
		else 
			echo " Error : Email not  existing"
			
		fi
	else
		echo "Error! File is not existing!"
	fi
}

delete()
{
	echo "Enter the address book name to display"
	read "ab"
	
	res= `ls | grep $ab | wc -w`
	
	if [ $res -gt 0 ]
	then 
		echo "Enter email"
		read email
		#check email is present in address book or not
		len= `cat $ab | grep $email | wc -w`	
		if [ $len -gt 0 ]
		then 
			
			old= `cat $ab | grep $email`
			
			sed -i s/"$old"//g $ab
			sed -i /^$/d $ab
			echo "Record Deleted!"
		else 
			echo " Error : Email not  existing"
			
		fi
	else
		echo "Error! File is not existing!"
	fi
}


while [ true ]
do
	echo "**********************"
	echo "1. Create"
	echo "2. Display"
	echo "3. Insert"
	echo "4. Modify"
	echo "5. Delete"
	echo "6. Exit"

	
	echo "Enter Choice"
	read choice
	
	case $choice in
		1) create ;;
		
		2) display ;;
		
		3) insert ;;
		
		4) modify ;;
		
		5) delete ;;
		
		6) exit ;;
		
		*) echo "Wrong Choice!" ;;
	esac
done
