There are two program file, command to execute server file
---------------------------------------------------
$ gcc server11.c -o server11 -lpthread

$ ./server11 ip-address

--------------------------------------------------

Command to execute client file


$ gcc client1.c -o client1 -lpthread

$ ./client1 ip-address_of_server

----------------------------------

There are two other files "cf.c" and "sf.c". These are for transferring file content. It is working but connection is lost after receiving the data.

Commands are:-

$ gcc sf.c -o sf 
$ ./sf

$ gcc cf.c -o cf
$ ./cf ip_address_of_server
