describe("binary operators", function () {
  test("simple addition", function () {
    expect(1 + 1).toBe(2);
  });

  test("addition with three arguments", function () {
    expect(1 + 1 + 1).toBe(3);
  });

  test("count to ten", function () {
    var i = 0;
    while (i < 10) {
      i = i + 1;
    }
    expect(i).toBe(10);
  });
});