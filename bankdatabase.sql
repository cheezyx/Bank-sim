account_privilege_idaccount_idcustomer_id

create user bankdatabase@'localhost' identified by 'bankdatabasepass';
grant all on bankdatabase.* to bankdatabase@'localhost';