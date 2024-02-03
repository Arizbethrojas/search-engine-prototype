`pagedir.c` has two methods within it. 
*  pagedir_init
*  pagedir_save

In `pagedir_init`, we create a crawler directory in pagedirectory and return a Boolean value representing whether that was done correctly. 

In  `pagedir_save`, we create a docID directory in pagedirectory and do not return anything because this method is `void`.
