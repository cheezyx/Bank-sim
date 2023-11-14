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
  add: function (card, callback) {
    bcrypt.hash(card.pin_hashed, saltRounds, function (err, hash) {
      if (err) {
        return callback(err);
      }
      db.query('insert into cards (customer_id, card_type, pin_hashed) values(?,?,?)',
        [card.customer_id, card.card_type, hash], function (err, result) {
          if (err) {
            return callback(err);
          }
          const cardId = result.insertId;

          // Tarkistetaan onko taulukko ja jos on...
          if (Array.isArray(card.account_ids) && card.account_ids.length > 0) {
            // Syötetään card_privilegesiin jokainen account_id mitä löytyy (tässä tietenkin vain yksi tai kaksi)
            card.account_ids.forEach(account_id => {
              db.query('insert into card_privileges (card_id, account_id) values(?,?)',
                [cardId, account_id], function (err) {
                  if (err) {
                    return callback(err);
                  }
                });
            });
          }

          callback(null, result);
        });
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
  }

}

module.exports = cards;