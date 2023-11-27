const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds = 10;
const cards = {
  getAll: function (callback) {
    return db.query('select * from cards', callback);
  },
  getById: function (id, callback) {
    return db.query('select * from cards where card_id=?', [id], callback);
  },

  getOwnerNameByCardId: function (card_id, callback) {
    return db.query(
      'SELECT c.first_name, c.last_name FROM cards as cd JOIN customers as c ON cd.customer_id = c.customer_id WHERE cd.card_id = ?',
      [card_id],
      callback
    );
  },

  addWithProcedure: function (card, account_ids, callback) {
    bcrypt.hash(card.pin_hashed, saltRounds, function (err, hash) {
      if (err) {
        return callback(err);
      }

      // Kutsu proseduuria. Oletetaan, että account_ids on taulukko.
      const account1_id = account_ids[0];
      const account2_id = account_ids.length > 1 ? account_ids[1] : null;

      db.query('CALL AddCardAndLinkAccount(?, ?, ?, ?, ?)',
        [card.customer_id, card.card_type, hash, account1_id, account2_id],
        callback
      );
    });
  },

  delete: function (id, callback) {
    return db.query('delete from cards where card_id=?', [id], callback);
  },
  update: function (id, cards, callback) {
    bcrypt.hash(cards.pin_hashed, saltRounds, function (err, hash) {
      return db.query('update cards set customer_id=?, card_type=?, pin_hashed=? where card_id=?',
        [cards.customer_id, cards.card_type, hash, id], callback);
    });
  },
  checkPassword:function(card_id, callback){
    return db.query('select pin_hashed from cards where card_id=?',[card_id],callback);
  }

}

module.exports = cards;