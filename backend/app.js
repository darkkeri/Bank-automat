var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var accountRouter = require('./routes/account');
var logsRouter = require('./routes/logs');
var userRouter = require('./routes/user');
var cardsRouter = require('./routes/cards');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/account', accountRouter);
app.use('/logs', logsRouter);
app.use('/user', userRouter);
app.use('/cards', cardsRouter);

module.exports = app;

