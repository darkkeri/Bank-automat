const express = require('express');
const router = express.Router();
const cards = require('../models/cards_model');

router.get('/',function(request, response){
    cards.getAllCards(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.post('/',function(request, response){
    cards.addCards(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.put('/:cardsid', function(request, response){
    cards.updateCards(request.params.cardsid, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.delete('/:cardsid', function(request, response){
    cards.deleteCards(request.params.cardsid, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
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

module.exports = router;
