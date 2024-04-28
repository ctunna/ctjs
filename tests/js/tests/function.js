describe("function", function() {
  test("closure holds state", function() {
    function closure() {
      var x = 1;
      return function() {
        return x;
      };
    }
    expect(closure()()).toBe(1);
  });

  test("recursion", function() {
    function factorial(n) {
      if (n < 2) {
        return 1;
      }
      return n * factorial(n - 1);
    }
    expect(factorial(3)).toBe(6);
  });
});
