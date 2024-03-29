const express = require('express');
const router = express.Router();
const card_privileges = require('../models/card_privileges_model');

router.get('/',
    function (request, response) {
        card_privileges.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/:id',
    function (request, response) {
        card_privileges.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });
    module.exports = router;