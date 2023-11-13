const db = require('../database');

const accounts = {
  getAll: function(callback) {
    return db.query('select * from accounts', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from accounts where account_id=?', [id], callback);
  },
  add: function(accounts, callback) {
    return db.query('insert into accounts (balance, account_type, credit_limit) values(?,?,?)',
      [accounts.balance, accounts.account_type, accounts.credit_limit],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from accounts where account_id=?', [id], callback);
  },
  update: function(id, accounts, callback) {
    return db.query(
      'update accounts set balance=?, account_type=?, credit_limit=? where account_id=?',
      [accounts.balance, accounts.account_type, accounts.credit_limit, id],
      callback
    );
  }
};
module.exports = accounts;