// #pragma once

// #include <execution>

// namespace grido {

//   template <typename Container>
//   class for_each_iterator {

//     template <typename Func>
//     void for_each(Container const & container, Func && func) {
//       for(auto const item: container) {
//         func(item);
//       }
//     }

//     template <typename Func>
//     void for_each(Container & container, Func && func) {
//       for(auto const item: container) {
//         func(item);
//       }
//     }

//     template <typename Func>
//     void for_each(Container && container, Func && func) {
//       for(auto const item: container) {
//         func(item);
//       }
//     }

//     // openmp
//     template <typename Func>
//     void for_each_parallel(Container const & container, Func && func) {
//       #pragma omp parallel for
//       for (auto iter = container.begin() ; iter != container.end() ; ++iter) {
//         func(*iter);
//       }
//     }

//     // openmp
//     template <typename Func>
//     void for_each_parallel(Container & container, Func && func) {
//       #pragma omp parallel for
//       for (auto iter = container.begin() ; iter != container.end() ; ++iter) {
//         func(*iter);
//       }
//     }
//     // openmp
//     template <typename Func>
//     void for_each_parallel(Container && container, Func && func) {
//       #pragma omp parallel for
//       for (auto iter = container.begin() ; iter != container.end() ; ++iter) {
//         func(*iter);
//       }
//     }
//   };


//   template <typename Container, typename Func>
//   void for_each(Container & container, Func && func) {
//     for_each_iterator<Container>
//     for(auto const item: container) {
//       func(item);
//     }
//   }

//   template <typename ExecutionPolicy, typename Container, typename Func>
//   void for_each(Container && container, Func && func) {
//     for(auto const item: container) {
//       func(item);
//     }
//   }



// };
