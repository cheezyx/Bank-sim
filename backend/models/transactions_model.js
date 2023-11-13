const db = require('../database');

const transactions = {
  getAll: function(callback) {
    db.query('SELECT * FROM transactions', callback);
  },
  getById: function(id, callback) {
    db.query('SELECT * FROM transactions WHERE transaction_id = ?', [id], callback);
  },
  add: function(transaction, callback) {
    db.query('INSERT INTO transactions (from_account_id, to_account_id, amount, date_time, description, transaction_type) VALUES (?, ?, ?, NOW(), ?, ?)',
      [transaction.from_account_id, transaction.to_account_id, transaction.amount, transaction.description, transaction.transaction_type],
      callback
    );
  },
  delete: function(id, callback) {
    db.query('DELETE FROM transactions WHERE transaction_id = ?', [id], callback);
  },
  update: function(id, transaction, callback) {
    db.query('UPDATE transactions SET from_account_id = ?, to_account_id = ?, amount = ?, description = ?, transaction_type = ? WHERE transaction_id = ?',
      [transaction.from_account_id, transaction.to_account_id, transaction.amount, transaction.description, transaction.transaction_type, id],
      callback
    );
  }
}

module.exports = transactions;