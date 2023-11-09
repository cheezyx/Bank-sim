const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const accounts={
  getAll: function(callback) {
    return db.query('select * from accounts', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from accounts where account_id=?', [id], callback);
  },
  add: function(accounts, callback) {
    bcrypt.hash(accounts.password, saltRounds, function(err, hash) {
      return db.query('insert into accounts (customer_id, balance, account_type, credit_limit) values(?,?,?,?)',
      [accounts.customer_id, accounts.balance, accounts.account_type, hash], callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from accounts where account_id=?', [id], callback);
  },
  update: function(id, accounts, callback) {
    bcrypt.hash(accounts.password, saltRounds, function(err, hash) {
      return db.query('update accounts set accountsname=?, password=? where account_id=?',
      [accounts.accountsname, hash, id], callback);
    });
  }

}
          
module.exports = accounts;