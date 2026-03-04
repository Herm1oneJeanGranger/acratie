class Neuron:

    def __init__(self, w, f = lambda x: x):
        self.w = w
        self.f = f
        self.last = None

    def forward(self, x):
        self.last = x
        res = sum(map(lambda i1, i2: i1 * i2, self.w, x))
        return self.f(res)
    def backlog(self):
        return self.last