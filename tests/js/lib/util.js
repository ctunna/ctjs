var Object = {
  keys: function(obj) {
    var keys = [];
    for (var key in obj) {
      keys.push(key);
    }
    return keys;
  },
  length: function(obj) {
    var total = 0;
    for (var _ in obj) {
      total = total + 1;
    }
    return total;
  }
};