# PhoneBook
This is a project in c , that was created for the needs of my university.
It is practicly a phonebook with basic option.

You run it like this:
```
/program.exe -f
```
I have a help option if you want to see all the commands:
```
/program.exe -h
```

You can create the phonebook (txt file ) like this: 
```
/program.exe -f "filename" -new
```

You can create then the Record :
```
/program.exe -f "filename" -newentry "Name" "Phone"
```

You can change the Record:
```
/program.exe -f "filename" -changeentry "OldName" "NewPhone"
```

You can show the Record:
```
/program.exe -f "filename" -changeentry "OldName" "Phone"
```

You can  show all  Records:
```
/program.exe -f "filename" -changeentries
```

You can delete a Record:
```
/program.exe -f "filename" -deleteentry "Name"
```

You can delete all Records:
```
/program.exe -f "filename" -deleteentries
```
