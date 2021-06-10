import React, { Component } from 'react';
// import Welcome from './pages/Welcome/Welcome';
import { BrowserRouter, Route, Switch } from "react-router-dom";
import Lobby from './pages/Lobby/Lobby';
import Attack from './pages/Attack/Attack';
import Danger from './pages/Danger/Danger';
import Dry from './pages/Dry/Dry';
import Safe from './pages/Safe/Safe';
import Tutorial from './pages/Tutorial/Tutorial';
import * as Webfontloader from "webfontloader";
import * as ReactDOM from "react-dom";

class App extends Component {
  public static render(baseEl: Element)
  {
    Webfontloader.load({
      google: {
        families: ["Egal Lake"]
      },
    });

    ReactDOM.render(<App />, baseEl);
  }

  public render()
  {
    return (
      <BrowserRouter>
        <Switch>
          <Route path="/lobby" component={Lobby} />
          <Route path="/attack/:slug" component={Attack} />
          <Route path="/dark" component={Danger} />
          <Route path="/dry" component={Dry} />
          <Route path="/safe" component={Safe} />
          <Route path="/tutorial" component={Tutorial} />
          <Route path="/" component={Lobby} />
        </Switch>
      </BrowserRouter>
    );
  }
}

export default App;
