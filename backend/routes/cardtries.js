const express = require('express');
const router = express.Router();
const cards = require('../models/cards_model');

router.post('/:idCards', function(request, response){
    cards.putTries(request.params.idCards, request.body.triesUnResettinator, function(err, result){
        if(err){
            response.send(err);
            response.json(false);
        }
        else{
            response.json(true);
        }
    });
});

router.get('/:cardsid', function(request, response){
    cards.getOneCard(request.params.cardsid, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    });
});

module.exports = router;
