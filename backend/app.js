var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var customersRouter = require('./routes/customers');
var cardsRouter = require('./routes/cards');
var transactionsRouter = require('./routes/transactions');
var accountsRouter = require('./routes/accounts');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/customers', customersRouter);
app.use('/cards', cardsRouter);
app.use('/transactions', transactionsRouter);
app.use('/accounts', accountsRouter);

module.exports = app;
