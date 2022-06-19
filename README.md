For using the project you need to open main.exe as  ".\main.exe 'type_of_user' 'username' 'password'"

Type_of_user can be "admin", "student", "studentaffair" or "lecturer"

For admin and studentaffair, username can be any string.
For lecturer, username is the lecturer's id.
For student, username is the student's number.

Password is the password of the user for all usertypes.

Windows 1254 encoding must be used for it to work properly with turkish characters.


Before the passwords are written to a file, they are encrypted with Caesar cipher.