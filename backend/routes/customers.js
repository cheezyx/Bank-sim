const express = require('express');
const router = express.Router();
const customers = require('../models/customers_model');

router.get('/',
    function (request, response) {
        customers.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });
    router.get('/:id', function(request, response) {
      customers.getById(request.params.id, function(err, dbResult) {
        if (err) {
          response.json(err);
        } else {
          response.json(dbResult);
        }
      });
    });
    router.get('/firstname/:first_name', function(request, response) {
      customers.getByFirst_name(request.params.first_name, function(err, dbResult) {
        if (err) {
          response.json(err);
        } else {
          response.json(dbResult);
        }
      });
    });


router.post('/', 
function(request, response) {
  customers.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  customers.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  customers.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


module.exports = router;
