const express = require('express');
const router = express.Router();
const user=require('../models/user_model');

router.get('/', function(request, response){
    user.getAllUser(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(result);
        }
    });
});

router.post('/', function(request, response){
    user.addUser(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(result);
        }
    });

});


router.put('/:id', function(request, response){

    user.updateUser(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(result);
    }});
});    

router.delete('/:id', function(request, response){
    user.deleteUser(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(result);   
        }});
}); 

router.get('/:id', function(request, response){
    user.getOneUser(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(result);
        }});
});

module.exports = router;