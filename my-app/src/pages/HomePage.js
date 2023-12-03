import React from 'react';
import { Link } from 'react-router-dom';

function HomePage() {
  return (
    <div>
      <h1>Tervetuloa Pankki Sovellukseen!</h1>
      <p>Tämä on sovelluksen kotisivu.</p>
      {/* Lisää Link-komponentti navigoidaksesi LoginPageen */}
      <Link to="/login">Kirjaudu sisään</Link>
    </div>
  );
}

export default HomePage;