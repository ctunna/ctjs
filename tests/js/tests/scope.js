describe("scope", function() {
  test("block statement with redeclaration", function() {
    var x = 1;
    {
      var x = 2;
      expect(x).toBe(2);
    }
    expect(x).toBe(1);
  });

  test("block statement with update", function() {
    var x = 1;
    {
      x = 2;
      expect(x).toBe(2);
    }
    expect(x).toBe(2);
  });
});
