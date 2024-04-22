const express = require('express');
const router = express.Router();
const account = require('../models/cards_model');

router.get('/', function(request, response){
        account.getCardIdByCardnum(request.body.cardnumber, function(err, result){
            if(err){
                console.log(err);
                response.json(err);
            }
            else{
                response.send(result);
            }
        });
});


module.exports = router;