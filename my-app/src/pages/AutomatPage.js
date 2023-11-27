import React, { useState, useEffect } from 'react';

    function AutomatPage() {
        const [name, setName] = useState('');
        const cardId = localStorage.getItem('card_id');
        const token = localStorage.getItem('token');
      
        useEffect(() => {
          if (cardId && token) {
            fetch(`http://localhost:3000/cards/owner/${cardId}`, {
              headers: {
                'Authorization': `Bearer ${token}`
              }
            })
            .then(response => {
              if (!response.ok) {
                throw new Error('Unauthorized');
              }
              return response.json();
            })
            .then(data => {
              if (data && data.length > 0) {
                const ownerName = `${data[0].first_name} ${data[0].last_name}`;
                setName(ownerName);
              }
            })
            .catch(error => {
              console.error('Error:', error);
            });
          }
        }, [cardId, token]);
      
        return (
          <div>
            {name ? <h1>Hei {name}!</h1> : <p>Ladataan...</p>}
          </div>
        );
      }

export default AutomatPage;