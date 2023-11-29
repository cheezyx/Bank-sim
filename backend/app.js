var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');
const cors = require('cors');

var indexRouter = require('./routes/index');
var customersRouter = require('./routes/customers');
var cardsRouter = require('./routes/cards');
var transactionsRouter = require('./routes/transactions');
var accountsRouter = require('./routes/accounts');
var loginRouter = require('./routes/login');
var card_privilegesRouter = require('./routes/card_privileges');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(cors({
  origin: 'http://localhost:3001',
}));

app.use('/', indexRouter);
app.use('/login', loginRouter);
app.use(authenticateToken);
//suojattu alapuolella olevat reitit
app.use('/customers', customersRouter);
app.use('/cards', cardsRouter);
app.use('/transactions', transactionsRouter);
app.use('/accounts', accountsRouter);
app.use('/card_privileges', card_privilegesRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.Tokeni, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }


module.exports = app;
