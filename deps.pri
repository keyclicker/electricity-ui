# Eigen 3 and Boost (header-only parts) for the app and the tests.
#
# Defaults: Eigen from pkg-config (`eigen3`), Boost from the compiler's
# default include path. Override with `qmake EIGEN_DIR=... BOOST_DIR=...`
# (e.g. on Windows: `EIGEN_DIR=C:/Libraries/Eigen`).

isEmpty(EIGEN_DIR) {
	CONFIG += link_pkgconfig
	PKGCONFIG += eigen3
} else {
	INCLUDEPATH += $$EIGEN_DIR
}

!isEmpty(BOOST_DIR) {
	INCLUDEPATH += $$BOOST_DIR
}
