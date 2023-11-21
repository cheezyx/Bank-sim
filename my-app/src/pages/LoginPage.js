import React, { useState } from 'react';

function LoginPage() {
    const [cardId, setCardId] = useState('');
    const [pin, setPin] = useState('');
  
    const handleSubmit = async (event) => {
      event.preventDefault();
      try {
        const response = await fetch('/login', { // Oletetaan että backendisi on samassa osoitteessa
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ card_id: cardId, pin_hashed: pin }),
        });
        const data = await response.json();
        if (data) {
          // Käsittely onnistuneen kirjautumisen jälkeen, esim. tokenin tallennus ja uudelleenohjaus
        } else {
          // Virheenkäsittely, jos kirjautuminen ei onnistu
        }
      } catch (error) {
        console.error('Kirjautumisessa tapahtui virhe:', error);
      }
    };

  return (
    <div>
      <h1>Kirjaudu sisään</h1>
      <form onSubmit={handleSubmit}>
        <label>
          Kortin ID:
          <input 
            type="text" 
            value={cardId} 
            onChange={(e) => setCardId(e.target.value)} 
            required 
          />
        </label>
        <label>
          PIN-koodi:
          <input 
            type="password" 
            value={pin} 
            onChange={(e) => setPin(e.target.value)} 
            required 
          />
        </label>
        <button type="submit">Kirjaudu</button>
      </form>
    </div>
  );
}

export default LoginPage;