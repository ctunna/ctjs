describe("arrays", function () {
  test("empty array", function () {
    var arr = [];
    var total = 0;
    for (var _ in arr) {
      total = total + 1;
    }
    expect(total).toBe(0);
  });

  test("single element", function () {
    var arr = [1];
    var total = 0;
    for (var index in arr) {
      total = total + arr[index];
    }
    expect(total).toBe(1);
  });

  test("multiple elements", function () {
    var arr = [1, 2, 3];
    var total = 0;
    for (var index in arr) {
      total = total + arr[index];
    }
    expect(total).toBe(6);
  });
});

