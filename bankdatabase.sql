account_privilege_idaccount_idcustomer_id

create user bankdatabaseuser@'localhost' identified by 'bankdatabasepass';
grant all on bankdatabase.* to bankdatabaseuser@'localhost';