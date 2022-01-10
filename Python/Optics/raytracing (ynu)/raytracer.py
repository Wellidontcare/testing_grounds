class raytracer:

    def __init__(self, distances_mm, focallengths_mm):
        self.update(distances_mm, focallengths_mm)

    def update(self, distances_mm, focallengths_mm):
        self._distance_list = [distance for distance in distances_mm]
        self._distance_list.append(0)
        self._focallength_list = [
            focallength for focallength in focallengths_mm]
        y1 = 1.0
        u0 = -y1 / self._distance_list[0]
        u = u0
        y = y1
        for i in range(len(self._focallength_list)):
            u -= (y / self._focallength_list[i])
            y += (self._distance_list[i+1]*u)
        if u == 0:
            self._distance_list[-1] = 0.0
        else:
            self._distance_list[-1] = -(y/u)
        self._projection_scale = u0/u

    def scaleFactor(self):
        return self._projection_scale
    def imagePos(self):
        return self._distance_list[-1]
