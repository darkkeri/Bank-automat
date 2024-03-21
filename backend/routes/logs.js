const express = require('express');
const router = express.Router();
const logs = require('../models/logs_model');

router.get('/',function(request, response){
    logs.getAllLogs(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.get('/:logsid',function(request,response)){
    
}

router.post('/',function(request, response){
    logs.addLogs(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.put('/:logsid', function(request, response){
    logs.updateLogs(request.params.logsid, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

module.exports = router;