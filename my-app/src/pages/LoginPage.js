import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';

function LoginPage() {
    const [cardId, setCardId] = useState('');
    const [pin, setPin] = useState('');
    const [message, setMessage] = useState('');
    const [isLoading, setIsLoading] = useState(false);
    const navigate = useNavigate();

    const handleSubmit = async (event) => {
      event.preventDefault();
      setIsLoading(true);
      try {
        const response = await fetch('http://localhost:3000/login', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ card_id: cardId, pin_hashed: pin }),
        });
    
        if (response.ok) {
          const token = await response.text(); // Käytä text-metodia vastauksen lukemiseen
          if (token && token !== 'false') {
            localStorage.setItem('token', token);
            setMessage('Login successful');
            localStorage.setItem('card_id', cardId); // Tallenna card_id local storageen
            navigate('/automat'); // Uudelleenohjaus AutomatPage-sivulle
            // TODO: Ohjaa käyttäjä eteenpäin tai päivitä tilaa
          } else {
            setMessage('Password incorrect or user does not exist');
          }
        } else {
          setMessage('An error occurred');
        }
      } catch (error) {
        console.error('Kirjautumisessa tapahtui virhe:', error);
        setMessage('An error occurred during login');
      } finally {
        setIsLoading(false);
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
          <button type="submit" disabled={isLoading}>
            {isLoading ? 'Loading...' : 'Kirjaudu'}
          </button>
        </form>
        {message && <p>{message}</p>}
      </div>
    );
}

export default LoginPage;