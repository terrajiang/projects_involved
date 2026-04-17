/**
Returns the result of rolling two dice.
Here are some possible return values.
. '1 + 2 = 3'
. '6 + 4 = 10'
. '3 + 5 = 8'
. '2 + 2 = 4'

The probability distribution of the return values
is the same as rolling two fair dice in real life.

@return {string} The result of rolling two dice.
*/
function roll_dice() {
  let i = Math.floor(1 + 6 * Math.random());
  let j = Math.floor(1 + 6 * Math.random());
  let sum = i + j;

  return `${i} + ${j} = ${sum}`;
}



/**
Deletes duplicates in an array of numbers.
Calling first_occurrences(arr) does not mutate the array referenced by arr.

@param {Array} arr : An array of numbers.
@return {Array} An array consisting of the same numbers in the same order as in arr.
				However, only the first occurrence of each number is included.
*/
function first_occurrences(arr) {
  let temp = [];

  if (arr.length === 0) {
    return [];
  } else {
    temp.push(arr[0]);
  }

  for (let i = 1; i < arr.length; ++i) {
    let repeated = false;

    for (let j = 0; j < temp.length; ++j) {
      if (temp[j] === arr[i]) {
        repeated = true;
        break;
      }
    }

    if (repeated === false) {
      temp.push(arr[i]);
    }
  }
  return temp;
}



/**
Removes elements of one array in accordance with another.
No new arrays are created during the function call.

Calling first_minus_second(arr1, arr2)
. mutates the array referenced by arr1:
all elements of arr1 that occur in arr2 are removed and
the order of the remaining elements is preserved.
. does not mutate the array referenced by arr2.

@param {Array} arr1 : The array to remove elements from.
@param {Array} arr2 : The array indicating which elements to remove.
*/
function first_minus_second(arr1, arr2) {
  for (let i = 0; i < arr1.length; ++i) {
    for (let j = 0; j < arr2.length; ++j) {
      if (arr2[j] === arr1[i]) {
        let index = arr1.indexOf(arr1[i]);
        arr1.splice(index, 1);
        --i;
      }
    }
  }
}



/**
This function extracts from a given cookie
the 'value' corresponding to the 'name' "username".

For example, both of the following function calls return "bur=nett":
. extract_username("first_name=Sarah; last_name=Burnett; username=bur=nett");
. extract_username("username=bur=nett; first_name=Sarah; last_name=Burnett");

If the given cookie has no 'name' called "username",
then the function returns the empty string.

For example, we have
. extract_username("common_error=Sara; " +
"another_one=Burnet; another=Sarah_Brunette") === "";

@param {string} cookie : The cookie to extract information from.
@return {string} The 'value' corresponding to the 'name' "username";
			the empty string if "username" is not a 'name'.
*/
function extract_username(cookie) {
  while (true) {
    let usernameId = cookie.indexOf('username=');

    if (usernameId === -1) {
      return '';
    } else {
      let postStr = cookie.substr(usernameId + 'username='.length);
      let semicolonId = postStr.indexOf(';');

      if (usernameId !== 0 && cookie[usernameId - 1] !== ' ') {
        cookie = postStr;
        continue;
      }

      if (semicolonId === -1) {
        return postStr;
      } else {
        return postStr.substring(0, semicolonId);
      }
    }
  }
}