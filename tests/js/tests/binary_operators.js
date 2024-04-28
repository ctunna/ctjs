describe("binary operators", function () {
  test("simple addition", function () {
    expect(1 + 1).toBe(2);
  });

  test("addition with three arguments", function () {
    expect(1 + 1 + 1).toBe(3);
  });

  // test("associativity", function () {
  //   expect(8 / 2 / 2).toBe(2);
  // });
});