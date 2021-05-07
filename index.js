import React from 'react';
import ReactDOM from 'react-dom';

class MyForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      algoritm: 'Regression',
      train_data_path: '',
      detect_data_path:'',
    };
  }

  mySubmitHandler = (event) => {
    //send to server
    event.preventDefault();
    alert("You are submitting " + this.state.algoritm);
  }

  myChangeHandler = (event) => {
    let filed = event.target.name;
    let val = event.target.value;
    this.setState({[filed]: val});
  }

  render() {
    return (
      <form onSubmit={this.mySubmitHandler} target="result">

      <h1>Anomaly Server Detect</h1>

      <select onChange={this.myChangeHandler} name='algoritm'>
        <option value="regression">Regression</option>
        <option value="hybrid">Hybrid</option>
      </select>

      <p>Enter a path to a CSV file without anomalies:</p>
      <input
        type='text'
        name='train_data_path'
        onChange={this.myChangeHandler}
      />
      <p>Enter a path to a CSV file you wish to detect:</p>
      <input
        type='text'
        name='detect_data_path'
        onChange={this.myChangeHandler}
      />
      <br></br>
      <br></br>

      <input
        type='submit'
        value='upload'
      />
      </form>
    );
  }
}

ReactDOM.render(<MyForm />, document.getElementById('root'));
