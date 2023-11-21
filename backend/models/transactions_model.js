const db = require('../database.js');

const transactionsmodel = {
  transferBalance: function(from_account_id, to_account_id, amount, description, transaction_type, callback) {
    db.query(
      'CALL TransferBalance(?, ?, ?, ?, ?, @message)',
      [from_account_id, to_account_id, amount, description, transaction_type],
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

  deposit: function(account_id, amount, description, callback) {
    db.query(
        'CALL DepositBalance(?, ?, ?, @message)',
        [account_id, amount, description],
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

withdraw: function(account_id, amount, description, callback) {
  db.query(
      'CALL WithdrawBalance(?, ?, ?, @message)',
      [account_id, amount, description],
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