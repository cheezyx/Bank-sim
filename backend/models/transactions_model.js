const db = require('../database.js');

const transactionsmodel = {

  getAll: function (callback) {
    return db.query('select * from transactions', callback);
  },
  getTransfersInByAccountID: function (id, callback) {
    return db.query('select * from transactions where to_account_id=?', [id], callback);
  },
  getTransfersOutByAccountID: function (id, callback) {
    return db.query('select * from transactions where from_account_id=?', [id], callback);
  },

  getAllTransfersByAccountID: function (account_id, callback) {
    return db.query('select * from transactions where from_account_id=? or to_account_id=?', [account_id, account_id], callback);
  },

  getTransactions: function (account_id, limit, offset, callback) {
    return db.query(
      'SELECT * FROM transactions WHERE (from_account_id = ? OR to_account_id = ?) ORDER BY transaction_id DESC LIMIT ? OFFSET ?',
      [account_id, account_id, limit, offset],
      function (err, results) {
        if (err) {
          callback(err, null);
        } else {
          if (results.length === 0) {
            callback(null, 'Ei tilitapahtumia');
          } else {
            callback(null, results);
          }
        }
      }
    );
  },

  getTransactionCountForAccount: function (account_id, callback) {
    return db.query(
      'SELECT COUNT(*) as count FROM transactions WHERE from_account_id = ? OR to_account_id = ?',
      [account_id, account_id],
      callback
    );
  },

  getLastFiveTransactions: function (account_id, callback) {
    return db.query(
      'SELECT * FROM transactions WHERE from_account_id = ? OR to_account_id = ? ORDER BY date_time DESC LIMIT 5',
      [account_id, account_id],
      function (err, results) {
        if (err) {
          callback(err, null);
        } else {
          if (results.length === 0) {
            callback(null, 'Ei tilitapahtumia');
          } else {
            callback(null, results);
          }
        }
      }
    );
  },

  transferBalance: function (from_account_id, to_account_id, amount, description, callback) {
    db.query(
      'CALL TransferBalance(?, ?, ?, ?, @message)',
      [from_account_id, to_account_id, amount, description],
      (err, results) => {
        if (err) {
          return callback(err, null);
        }
        db.query('SELECT @message AS message', (err, results) => {
          return callback(err, results[0]);
        });
      }
    );
  },


  deposit: function (account_id, amount, callback) {
    db.query(
      'CALL DepositBalance(?, ?, @message)',
      [account_id, amount],
      (err, results) => {
        if (err) {
          return callback(err, null);
        }
        db.query('SELECT @message AS message', (err, results) => {
          return callback(err, results[0]);
        });
      }
    );
  },

  withdraw: function (account_id, amount, callback) {
    db.query(
      'CALL WithdrawBalance(?, ?, @message)',
      [account_id, amount],
      (err, results) => {
        if (err) {
          if (callback) return callback(err, null);
          else throw err;
        }
        db.query('SELECT @message AS message', (err, results) => {
          if (err) {
            if (callback) return callback(err, null);
            else throw err;
          }
          if (callback) return callback(null, results[0]);
        });
      }
    );
  },
};

module.exports = transactionsmodel;