const express = require('express');
const router = express.Router();
const account = require('../models/cards_model');

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