const db = require('../database');

const accounts = {
  getAll: function(callback) {
    return db.query('select * from accounts', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from accounts where account_id=?', [id], callback);
  },
  add: function(accounts, callback) {
    return db.query('START TRANSACTION; INSERT INTO accounts(balance, account_type, credit_limit) VALUES(?, ?, ?); SET @account_id = LAST_INSERT_ID(); INSERT INTO account_privileges(customer_id, account_id, access_level) VALUES(?, @account_id, ?); COMMIT;',
    [accounts.balance, accounts.account_type, accounts.credit_limit, accounts.customer_id, accounts.access_level], callback);
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