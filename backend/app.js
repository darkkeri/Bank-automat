var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var accountRouter = require('./routes/account');
var logsRouter = require('./routes/logs');
var userRouter = require('./routes/user');
var cardsRouter = require('./routes/cards');
var loginRouter = require('./routes/login');
var accountIdRouter = require('./routes/accountId');
var cardsIdRouter = require('./routes/cardsId');
var cardtypeRouter = require('./routes/cardtype');
var cardtriesRouter = require('./routes/cardtries');



var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

//suojaamattomat reitit
app.use('/', indexRouter);
app.use('/cardsId',cardsIdRouter);
app.use('/cardtype', cardtypeRouter);
app.use('/cards', cardtriesRouter);
app.use('/login', loginRouter);


app.use(authenticateToken);
//suojatut reitit
app.use('/accountId', accountIdRouter);
app.use('/account', accountRouter);
app.use('/logs', logsRouter);
app.use('/user', userRouter);
app.use('/cards', cardsRouter);


function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)

      req.user = user
  
      next()
    })
}


module.exports = app;

