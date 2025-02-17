/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:30:59 by yushsato          #+#    #+#             */
/*   Updated: 2025/02/16 03:26:10 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "config/single_alias.hpp"
#include "config/single_listen.hpp"

int socket_create()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		write(2, "Error: Socket creation failed\n", 31);
		return (-1);
	}
	return (server_fd);
}

int socket_bind(int server_fd, struct sockaddr_in *sa)
{
	if (bind(server_fd, (struct sockaddr *)sa, sizeof(*sa)) < 0)
	{
		write(2, "Error: Socket bind failed\n", 27);
		close(server_fd);
		return (-1);
	}
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		write(2, "Error: socket failed\n", 22);
		close(server_fd);
		return (-1);
	}
	return (0);
}

int socket_listen(int server_fd)
{
	if (listen(server_fd, 10) < 0)
	{
		write(2, "Error: Listen failed\n", 22);
		close(server_fd);
		return (-1);
	}
	return (0);
}

int main(int ac, char *av[])
{
	(void)ac;
	int server_fd = socket_create();
	struct sockaddr_in address;
	Alias alias(av[1]);
	std::cout << "Log: " << alias.Get() << std::endl;
	Listen listen(av[2]);
	std::cout << "Log: " << listen.Get() << std::endl;

			std::cout
		<< "[" << __FILE__ << "]" << __func__ << ":" << __LINE__ << "\t <Socket fd> \t" << server_fd << std::endl;
	if (server_fd < 0)
		return (0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if (socket_bind(server_fd, &address) || socket_listen(server_fd))
		return (1);

	while (true)
	{
		int new_socket = accept(server_fd, NULL, NULL);
		if (new_socket < 0)
		{
			write(2, "Accept failed\n", 15);
			continue;
		}

		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		read(new_socket, buffer, BUFFER_SIZE);
		write(new_socket, "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!", 53);

		close(new_socket);
		std::cout << "[" << __FILE__ << "]" << __func__ << ":" << __LINE__ << "\t <Socket fd> \t" << server_fd << std::endl;
	}
	return (0);
}
