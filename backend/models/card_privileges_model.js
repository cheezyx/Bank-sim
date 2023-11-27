const db = require('../database');

const card_privileges = {
  getAll: function(callback) {
    return db.query('select * from card_privileges', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from card_privileges where card_id=?', [id], callback);
  },
};
module.exports = card_privileges;