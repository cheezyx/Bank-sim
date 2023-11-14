const db = require('../database');

const customers = {
  getAll: function (callback) {
    return db.query('select * from customers', callback);
  },
  getById: function (id, callback) {
    return db.query('select * from customers where customer_id=?', [id], callback);
  },
  getByFirst_name: function (first_name, callback) {
    return db.query('select * from customers where first_name=?', [first_name], callback);
  },
  add: function (customers, callback) {
    return db.query('insert into customers (first_name, last_name) values(?,?)',
      [customers.first_name, customers.last_name],
      callback
    );

  },
  delete: function (id, callback) {
    return db.query('delete from customers where customer_id=?', [id], callback);
  },
  update: function (id, customers, callback) {
    return db.query('update customers set first_name=?, last_name=? where customer_id=?',
      [customers.first_name, customers.last_name, id],
      callback
    );
  }
}


module.exports = customers;  