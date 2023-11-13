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
      return db.query('BEGIN; INSERT INTO accounts(balance, account_type, credit_limit) VALUES(?, ?, ?); INSERT INTO account_privileges(customer_id, account_id, access_level) VALUES(?, (SELECT account_id FROM accounts ORDER BY account_id DESC LIMIT 1), ?); COMMIT;',
      [accounts.balance, accounts.account_type, accounts.credit_limit, accounts.customer_id, accounts.access_level], callback);
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