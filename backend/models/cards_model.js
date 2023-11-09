const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const cards={
  getAll: function(callback) {
    return db.query('select * from cards', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from cards where card_id=?', [id], callback);
  },
  add: function(cards, callback) {
    bcrypt.hash(cards.pin_hashed, saltRounds, function(err, hash) {
      return db.query('insert into cards (customer_id, card_type, pin_hashed) values(?,?,?)',
      [cards.customer_id, cards.card_type, hash], callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from cards where card_id=?', [id], callback);
  },
  update: function(id, cards, callback) {
    bcrypt.hash(cards.pin_hashed, saltRounds, function(err, hash) {
      return db.query('update cards set customer_id=?, card_type=?, pin_hashed=? where card_id=?',
      [cards.customer_id, cards.card_type, hash, id], callback);
    });
  }

}
          
module.exports = cards;