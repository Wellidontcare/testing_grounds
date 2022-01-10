from raytracer import raytracer
def main():
    distances_mm = [int(distance) for distance in str(input("Please input the distances comma sperarated: ")).split(',')]
    focallengths_mm = [int(focallength) for focallength in str(input("Please input the focalllengths comma separated: ")).split(',')]
    r = raytracer(distances_mm, focallengths_mm)
    print("Scalefactor: " + str(r.scaleFactor()))
    print("Image is at: " + str(r.imagePos()) + " mm")
    

if __name__ == "__main__":
    main()